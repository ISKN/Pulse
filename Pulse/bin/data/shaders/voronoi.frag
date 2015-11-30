#version 110

uniform sampler2D white_noise_texture;
uniform vec4 globalColor;

uniform float time;
uniform vec2 resolution;

vec2 hash2( vec2 p )
{
	// texture based white noise
	return texture2D( white_noise_texture, (p+0.5)/256.0, -100.0 ).xy;
    // procedural white noise	
	//return fract(sin(vec2(dot(p,vec2(127.1,311.7)),dot(p,vec2(269.5,183.3))))*43758.5453);
}

vec3 voronoi( in vec2 x )
{
    vec2 n = floor(x);
    vec2 f = fract(x);

    //----------------------------------
    // first pass: regular voronoi
    //----------------------------------
	vec2 mg, mr;

    float md = 8.0;
    for(int j=-1; j<=1; j++ )
    for(int i=-1; i<=1; i++ )
    {
        vec2 g = vec2(float(i),float(j));
		vec2 o = hash2( n + g );

        o = 0.5 + 0.5*sin( time + 6.2831*o );

        vec2 r = g + o - f;
        float d = dot(r,r);

        if( d<md )
        {
            md = d;
            mr = r;
            mg = g;
        }
    }

    //----------------------------------
    // second pass: distance to borders
    //----------------------------------
    md = 8.0;
    for( int j=-2; j<=2; j++ )
    for( int i=-2; i<=2; i++ )
    {
        vec2 g = mg + vec2(float(i),float(j));
		vec2 o = hash2( n + g );
		
        o = 0.5 + 0.5*sin( time + 6.2831*o );

        vec2 r = g + o - f;

        if( dot(mr-r,mr-r)>0.00001 )
        md = min( md, dot( 0.5*(mr+r), normalize(r-mr) ) );
    }

    return vec3( md, mr );
}

void main()
{
    vec3 c = voronoi( 8.0* (gl_FragCoord.xy/resolution.xx) );

	// isolines
    vec3 col = c.x*(0.0 + 0.3*sin(2.0*c.x))*vec3(1.0);
    // borders	
    col = mix( vec3(0.2), col, smoothstep( 0.01, 0.02, c.x ) );

	gl_FragColor = vec4(col,1.0);
}
