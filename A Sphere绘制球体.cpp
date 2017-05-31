struct Ray {
	vec3 origin; 
	vec3 direction; 
};
    
struct Sphere {
	vec3 center;  
	float radius; 
};
 
//！！！
vec4 diffuse(in vec3 surface, in vec3 center, in vec4 color, in vec3 litePos) {
	// Surface normal
	vec3 n = normalize(surface - center)/1.2;
	
	// Light direction from surface
	vec3 l = normalize(litePos - surface)/1.2;

	// The diffuse equation
	return color * max(0.0, dot(n, l));
}
    
float intersectSphere(in Ray ray, in Sphere sphere) {
	vec3 co = ray.origin - sphere.center;

	float discriminant = dot(co, ray.direction) * dot(co, ray.direction)
			- (dot(co, co) - sphere.radius * sphere.radius);

	if (discriminant >= 0.0)
		return -dot(ray.direction, co) - sqrt(discriminant);
	else
		return -1.;
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    float x = fragCoord.x / iResolution.x; 
	float y = fragCoord.y*.6 / iResolution.y; 
    
    x = x * 2.0 - 1.0;
	y = y * 2.0 - 1.0;
    
    vec3 pixelPos = vec3(x, y, -1);

    vec3 eyePos = vec3(0, 0, -4); 
    
	vec3 rayDir = normalize(pixelPos - eyePos);
    
    Sphere sphere = Sphere(vec3(0.0, -1., 5.0), 1.0); 

	float eyeToSphere = intersectSphere(Ray(eyePos, rayDir), sphere);
    
   	if (eyeToSphere >= 0.)
	{
		//漫射颜色
		vec4 diffuseColour =  vec4(0.6,0.6,1.,1.);

		//周边颜色
		vec4 ambientColour =  vec4(0.9,0.4,0.,7);

        //光亮位置
        vec3 litePos = vec3(9., 10., 1.);
        
		fragColor = ambientColour + diffuse(eyePos + eyeToSphere * rayDir, sphere.center, diffuseColour, litePos);

	} else
		fragColor = vec4(0.9, 0.6, 0.6, 1);
}


