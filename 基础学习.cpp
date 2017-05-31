float linearstep(float edge0, float edge1, float x) {
    float t = (x - edge0)/(edge1 - edge0);
    return clamp(t, 0.0, 1.0);
}

float smootherstep(float edge0, float edge1, float x) {
    float t = (x - edge0)/(edge1 - edge0);
    float t1 = t*t*t*(t*(t*6. - 15.) + 10.);
    return clamp(t1, 0.0, 1.0);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord )
{
    vec2 r =  2.0*vec2(fragCoord.xy - 0.5*iResolution.xy)/iResolution.y;
    vec3 bgcol = vec3(1.0,0.3,0.5);//bg color
    vec3 col1 = vec3(0.4,0.2,0.5);//circle
    vec2 center1 = vec2(-1.35,0);
    vec2 center2 = vec2(-0.45,0);
    vec2 center3 = vec2(0.45,0);
    vec2 center4 = vec2(1.35,0);
    vec3 pixel = bgcol;
    float m=0.4;
    
    pixel = bgcol; 
    
    //circle 0
    //未经任何处理
    /*
    if(r.x<-0.9){
        if(length(r-center1)<m){
            pixel = col1;
        }
    }
    */
    
    //circle 1
    //step处理，等同于未经任何处理的circle 0 
    if(r.x<-0.9){
        m =  step(m,length(r-center1));
        pixel = mix(col1,bgcol,m);
    } 
    
    //circle 2
    //linearstep处理
    else if(r.x<-0.0){
        m =  linearstep(m-0.005,m+0.005,length(r-center2));
        pixel = mix(col1,bgcol,m);
    }
    
    //circle 3
    //smoothstep处理
    else if(r.x<0.9){
           m =  smoothstep(m-0.005,m+0.005,length(r-center3));
        pixel = mix(col1,bgcol,m);
    }
    
    //circle 4
    //自定义smootherstep处理
    else if(r.x<1.8){
           m =  smootherstep(m-0.005,m+0.005,length(r-center4));
        pixel = mix(col1,bgcol,m);
    }
 
    //区域分解线
    for(float i= -.9;i<2.0;i += 0.9){
        if(r.x<i && r.x>i-0.01)
            pixel = vec3(1.0);
    }
    
    fragColor = vec4(pixel,1.0);
}