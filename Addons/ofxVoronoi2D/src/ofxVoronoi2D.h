/*
 * OpenFramework wrapper for Shane O Sullivans' implementation of Steven Fortune's
 * sweep line algorithm.
 *
 * Released under the MIT License (MIT)
 *
 * Copyright (c) 2014 Alexandre Kaspar <alexandre.kaspar@a3.epfl.ch>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#pragma once

// #include <iostream>
#include <limits>
#include <map>
#include "ofMain.h"
#include "VoronoiDiagramGenerator.h"

using ofx::VoronoiDiagramGenerator;

struct ofxVec2fCompare {
  explicit ofxVec2fCompare(float minDist = 0.0f) : minSqDist(minDist * minDist) {}
  float minSqDist;
  // lexicographic ordering
  // @see http://stackoverflow.com/questions/8333936/stdmap-unique-stdless-function-for-a-2d-point-as-key
  bool operator ()(const ofVec2f &v1, const ofVec2f &v2) const {
    // v1 < v2
    if( v1.squareDistance(v2) < minSqDist) return false;
    return v1.x < v2.x || (v2.x == v1.x && v1.y < v2.y);
  }
};

struct ofxSegment {
  ofVec2f p1, p2;
};

class ofxSegmentIterator{
  public:
    explicit ofxSegmentIterator(VoronoiDiagramGenerator *vdg) : v(vdg), hasNext(true){
      v->resetIterator();
      consume();
    }
    operator bool() const {
      return hasNext;
    }
    ofxSegment operator *() const {
      return e;
    }
    ofxSegmentIterator &operator++() {
      consume();
      return *this;
    }
  private:
    void consume() {
      if(hasNext){
        hasNext = v->getNext(e.p1.x, e.p1.y, e.p2.x, e.p2.y);
      }
    }

    VoronoiDiagramGenerator *v;
    ofxSegment e;
    bool hasNext;
};

class ofxVoronoi2D {
  public:
    explicit ofxVoronoi2D(float mdist = 1e-6) : minDist(mdist){}

    template<typename T>
    void compute(const vector<T> &pts, const ofRectangle &bounds, float minSiteDist = -1.0f){
      if(minSiteDist < 0.0f)
        minSiteDist = getMinDist(pts);
      vector<float> xPts, yPts;
      const int N = pts.size();
      xPts.reserve(N);
      yPts.reserve(N);
      for(int i = 0; i < N; ++i){
        const T &p = pts[i];
        xPts.push_back(p.x);
        yPts.push_back(p.y);
      }

      // real computation
      voro.generateVoronoi(&xPts[0], &yPts[0], N,
        bounds.getMinX(), bounds.getMaxX(),
        bounds.getMinY(), bounds.getMaxY(),
      minSiteDist);
    }

    ofxSegmentIterator edges(){
      return ofxSegmentIterator(&voro);
    }

    /**
     * Build a mesh out of the Voronoi diagram
     *
     * @param mesh the mesh to append data to
     */
    void buildMesh(ofMesh &mesh, bool uniqIndices = true){
      if(uniqIndices) buildOptMesh(mesh);
      else buildTrivialMesh(mesh);
    }

    void setMinDist(float mdist) {
      minDist = mdist;
    }

    template<typename T>
    static float getMinDist(const vector<T> &pts) {
      // brute-force, no kd-tree or space splitting here
      // TODO use something smarter
      float minDist = std::numeric_limits<float>::max();
      for(int i = 0; i < pts.size() - 1; ++i){
        const T &p1 = pts[i];
        for(int j = i + 1; j < pts.size(); ++j){
          const T &p2 = pts[j];
          float d = ofDist(p1.x, p1.y, p2.x, p2.y);
          if(d < minDist) minDist = d;
        }
      }
      return minDist + std::numeric_limits<float>::epsilon();
    }

  private:
    VoronoiDiagramGenerator voro;
    float minDist;

    void buildOptMesh(ofMesh &mesh){
      typedef unsigned int Index;
      ofxVec2fCompare comp(minDist);
      std::map<ofVec2f, Index, ofxVec2fCompare> vind(comp);

      // register uniques vertices
      voro.resetIterator();
      ofVec2f p[2];
      ofVec2f s[2];
      int sites;
      while(voro.getNext(p[0], p[1], s[0], s[1], sites)){
        // std::cout << ". graph edge (" << sites << " sites)\n";
        for(int i = 0; i < 2; ++i){
          if(vind.find(p[i]) == vind.end()){
            vind.insert(std::pair<ofVec2f, Index>(p[i], vind.size()));
            mesh.addVertex(ofVec3f(p[i]));
            // std::cout << "new v " << p[i] << "\n";
          }
        }
        for(int i = 0; i < sites; ++i){
          if(vind.find(s[i]) == vind.end()){
            vind.insert(std::pair<ofVec2f, Index>(s[i], vind.size()));
            mesh.addVertex(ofVec3f(s[i]));
            // std::cout << "new s " << s[i] << "\n";
          }
        }
      }

      // register triangles = (index triplets)
      // Note: 1st index = voronoi cell center
      voro.resetIterator();
      while(voro.getNext(p[0], p[1], s[0], s[1], sites)){
        Index e1 = vind[p[0]], e2 = vind[p[1]];
        for(int j = 0; j < sites; ++j){
          Index cellInd = vind[s[j]];
          // TODO use correct ordering (c, e1, e2) or (c, e2, e1) depending on cross-product
          mesh.addTriangle(cellInd, e1, e2);
          // std::cout << "new t (" << cellInd << ", " << e1 << ", " << e2 << ")\n";
        }
      }
      mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }

    void buildTrivialMesh(ofMesh &mesh){
      typedef unsigned int Index;

      // register vertices
      voro.resetIterator();
      ofVec2f p[2];
      ofVec2f s[2];
      int sites;

      // register triangles = (index triplets)
      // Note: 1st index = voronoi cell center
      voro.resetIterator();
      while(voro.getNext(p[0], p[1], s[0], s[1], sites)){
        std::cout << ". graph edge (" << sites << " sites)\n";
        Index i = mesh.getVertices().size();
        // std::cout << "idx " << mesh.getIndices().size();
        // std::cout << ", vtx " << mesh.getVertices().size() << "\n";
        mesh.addVertex(ofVec3f(p[0]));
        mesh.addVertex(ofVec3f(p[1]));
        // std::cout << "e0 " << p[0] << ", e1 " << p[1] << "\n";
        for(int j = 0; j < sites; ++j){
          std::cout << "s" << j << " " << s[j] << "\n";
          mesh.addVertex(ofVec3f(s[j]));
          mesh.addTriangle(i + 2 + j, i, i + 1);

        }

      }
      mesh.setMode(OF_PRIMITIVE_TRIANGLES);
    }
};

