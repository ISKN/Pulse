#version 110


uniform vec2 mouse;

void main()
{
    gl_TexCoord[0] = gl_MultiTexCoord0;
	
	//get our current vertex position so we can modify it
	vec4 pos = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
	
	//lets also figure out the distance between the mouse and the vertex and apply a repelling force away from the mouse
	vec2 d = pos.xy - mouse;
	float len =  sqrt(d.x*d.x + d.y*d.y);
	float maxLen = 200.0;
	float repulsion = 35.0;
	if( len < maxLen && len > 0.0  ){
		
		//lets get the distance into 0-1 ranges
		float pct = len / maxLen; 
		
		//this turns our linear 0-1 value into a curved 0-1 value
		pct *= pct;

		//flip it so the closer we are the greater the repulsion
		pct = 1.0 - pct;
		
		//normalize our repulsion vector
		d /= len;
		
		//apply the repulsion to our position
		pos.xy += d.xy * pct * repulsion;
	}
	
	//finally set the pos to be that actual position rendered
	gl_Position = pos;
	gl_FrontColor = gl_Color;
}
