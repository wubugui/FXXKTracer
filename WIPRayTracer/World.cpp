#include "World.h"
#include "BaseGeometryObject.h"
#include "Ray.h"
#include "TraceData.h"
#include "ViewPanel.h"
#include "PanelObject.h"
#include "SphereObject.h"
#include <iostream>
#include "Header.h"
#include "Vector2.h"
#include "PhongMat.h"

typedef struct
{
	//unsigned short    bfType;  
	unsigned long    bfSize;
	unsigned short    bfReserved1;
	unsigned short    bfReserved2;
	unsigned long    bfOffBits;
} ClBitMapFileHeader;

typedef struct
{
	unsigned long  biSize;
	long   biWidth;
	long   biHeight;
	unsigned short   biPlanes;
	unsigned short   biBitCount;
	unsigned long  biCompression;
	unsigned long  biSizeImage;
	long   biXPelsPerMeter;
	long   biYPelsPerMeter;
	unsigned long   biClrUsed;
	unsigned long   biClrImportant;
} ClBitMapInfoHeader;

typedef struct
{
	unsigned char rgbBlue; //该颜色的蓝色分量  
	unsigned char rgbGreen; //该颜色的绿色分量  
	unsigned char rgbRed; //该颜色的红色分量  
	unsigned char rgbReserved; //保留值  
} ClRgbQuad;

typedef struct
{
	int width;
	int height;
	int channels;
	unsigned char* imageData;
}ClImage;


bool clSaveImage(char* path, ClImage* bmpImg);
bool clSaveImage(char* path, ClImage* bmpImg)
{
	FILE *pFile;
	unsigned short fileType;
	ClBitMapFileHeader bmpFileHeader;
	ClBitMapInfoHeader bmpInfoHeader;
	int step;
	int offset;
	unsigned char pixVal = '\0';
	int i, j;
	ClRgbQuad* quad;

	pFile = fopen(path, "wb");
	if (!pFile)
	{
		return false;
	}

	fileType = 0x4D42;
	fwrite(&fileType, sizeof(unsigned short), 1, pFile);

	if (bmpImg->channels == 3)//24位，通道，彩图  
	{
		step = bmpImg->channels*bmpImg->width;
		offset = step % 4;
		if (offset != 4)
		{
			step += 4 - offset;
		}

		bmpFileHeader.bfSize = bmpImg->height*step + 54;
		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfOffBits = 54;
		fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);

		bmpInfoHeader.biSize = 40;
		bmpInfoHeader.biWidth = bmpImg->width;
		bmpInfoHeader.biHeight = bmpImg->height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 24;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImage = bmpImg->height*step;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.biClrUsed = 0;
		bmpInfoHeader.biClrImportant = 0;
		fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);

		for (i = 0; i <bmpImg->height; i++)
		{
			for (j = 0; j < bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3 + 1];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				pixVal = bmpImg->imageData[i*bmpImg->width * 3 + j * 3 + 2];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset != 0)
			{
				for (j = 0; j < offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	else if (bmpImg->channels == 1)//8位，单通道，灰度图  
	{
		step = bmpImg->width;
		offset = step % 4;
		if (offset != 4)
		{
			step += 4 - offset;
		}

		bmpFileHeader.bfSize = 54 + 256 * 4 + bmpImg->width;
		bmpFileHeader.bfReserved1 = 0;
		bmpFileHeader.bfReserved2 = 0;
		bmpFileHeader.bfOffBits = 54 + 256 * 4;
		fwrite(&bmpFileHeader, sizeof(ClBitMapFileHeader), 1, pFile);

		bmpInfoHeader.biSize = 40;
		bmpInfoHeader.biWidth = bmpImg->width;
		bmpInfoHeader.biHeight = bmpImg->height;
		bmpInfoHeader.biPlanes = 1;
		bmpInfoHeader.biBitCount = 8;
		bmpInfoHeader.biCompression = 0;
		bmpInfoHeader.biSizeImage = bmpImg->height*step;
		bmpInfoHeader.biXPelsPerMeter = 0;
		bmpInfoHeader.biYPelsPerMeter = 0;
		bmpInfoHeader.biClrUsed = 256;
		bmpInfoHeader.biClrImportant = 256;
		fwrite(&bmpInfoHeader, sizeof(ClBitMapInfoHeader), 1, pFile);

		quad = (ClRgbQuad*)malloc(sizeof(ClRgbQuad) * 256);
		for (i = 0; i < 256; i++)
		{
			quad[i].rgbBlue = i;
			quad[i].rgbGreen = i;
			quad[i].rgbRed = i;
			quad[i].rgbReserved = 0;
		}
		fwrite(quad, sizeof(ClRgbQuad), 256, pFile);
		free(quad);

		for (i = bmpImg->height - 1; i > -1; i--)
		{
			for (j = 0; j < bmpImg->width; j++)
			{
				pixVal = bmpImg->imageData[i*bmpImg->width + j];
				fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
			}
			if (offset != 0)
			{
				for (j = 0; j < offset; j++)
				{
					pixVal = 0;
					fwrite(&pixVal, sizeof(unsigned char), 1, pFile);
				}
			}
		}
	}
	fclose(pFile);

	return true;
}
World::World()
{
	//test
	
}


World::~World()
{
	
}

void World::build(int num)
{
	phong_mat[0] = new PhongMat();
	phong_mat[0]->cd = RBVector3(1.f, 0, 0);
	phong_mat[0]->cs = RBVector3(1.5,0.0, 0.0);
	phong_mat[0]->kd = 0.8f;
	phong_mat[0]->kspec = 8.f;

	phong_mat[1] = new PhongMat();
	phong_mat[1]->cd = RBVector3(0.f, 0.f, 1.f);
	phong_mat[1]->cs = RBVector3(0.2, 0.2, 0.2);
	phong_mat[1]->kd = 0.8f;
	phong_mat[1]->kspec = 1.f;

	phong_mat[2] = new PhongMat();
	phong_mat[2]->cd = RBVector3(1.f, 0.8f, 1.f);
	phong_mat[2]->cs = RBVector3(1, 1, 1);
	phong_mat[2]->kd = 0.1f;
	phong_mat[2]->kspec = 1.f;

	phong_mat[3] = new PhongMat();
	*phong_mat[3] = *phong_mat[1];
	phong_mat[3]->cd = RBVector3(1.f, 0.9215686f, 0.01568628f);
	phong_mat[3]->cs = RBVector3(1.f, 0.9215686f, 0.01568628f);

	SphereObject* o1 = new SphereObject();
	o1->position.x = -0.4f;
	o1->position.y = 0.f;
	o1->position.z =1.f;
	o1->r = 1.f;
	o1->color.r = 0.0;
	o1->color.g = 0.0;
	o1->color.b = 1.0;
	o1->color.a = 1.0;
	o1->mat = phong_mat[0];

	SphereObject* o11 = new SphereObject();
	o11->position.x = 0.7f;
	o11->position.y = 0.1f;
	o11->position.z = 0.3f;
	o11->r = 0.4f;
	o11->color.r = 1.0;
	o11->color.g = 0.0;
	o11->color.b = 0.0;
	o11->color.a = 1.0;
	o11->mat = phong_mat[1];

	SphereObject* o111 = new SphereObject();
	o111->position.x = 0.2f;
	o111->position.y = -0.3f;
	o111->position.z = -0.3f;
	o111->r = 0.2f;
	o111->color = RBColorf::yellow;
	o111->mat = phong_mat[3];

	PanelObject* p = new PanelObject();
	p->color.r = 0.9;
	//p->color.g = p->color.b = p->color.a = 0.5f;
	p->color = RBColorf::cyan;
	p->normal.x = 0;
	p->normal.y = 0.8f;
	p->normal.z = -0.1f;
	p->point.x = 0;
	p->point.y = -0.7;
	p->point.z = 0;
	p->mat = phong_mat[2];
	

	_objects.push_back(o1);
	_objects.push_back(o11);
	_objects.push_back(p);
	_objects.push_back(o111);
}

void World::render()
{
	TraceData _trace_data;
	ViewPanel panel(800,800);
	_out_image = new unsigned char[panel.vsize*panel.hsize * 3];
	Ray ray;
	RBColorf c(0,0,0,1.f);
	for (int i = 0; i < panel.vsize; ++i)
	{
		for (int j = 0; j < panel.hsize; ++j)
		{
			panel.emit_ray(i,j,ray, _trace_data);
			c = trace_ray(ray, _trace_data,1);

			tone(c);

			_out_image[i*panel.hsize * 3 + j * 3] = (unsigned char)(c.b * 255);
			_out_image[i*panel.hsize * 3 + j * 3 + 1] = (unsigned char)(c.g * 255);
			_out_image[i*panel.hsize * 3 + j * 3 + 2] = (unsigned char)(c.r * 255);
		}
	}
}

/*
A = Shoulder Strength
B = Linear Strength
C = Linear Angle
D = Toe Strength
E = Toe Numerator
F = Toe Denominator
Note : E / F = Toe Angle
	   LinearWhite = Linear White Point Value
	   F(x) = ((x*(A*x + C*B) + D*E) / (x*(A*x + B) + D*F)) - E / F;
FinalColor = F(LinearColor) / F(LinearWhite)‏

http://blog.csdn.net/toughbro/article/details/6745207
http://filmicgames.com/archives/75
*/

RBVector3 World::_tonemap(RBVector3 x)
{
	float A = 0.15;
	float B = 0.50;
	float C = 0.10;
	float D = 0.20;
	float _E = 0.02;
	float F = 0.30;
	

	return ((x*(A*x + C*B) + D*_E) / (x*(A*x + B) + D*F)) - _E / F;
}

void World::tone(RBColorf& c)
{
	/*
	float u = RBMath::max3(c.r, c.g, c.b);
	if (u < 1.0f)
		return;
	float inv = 1.f/u;
	c*=inv;
	*/
	float W = 11.2;
	RBVector3 texColor(c);
	texColor *= 1.5f;  // Hardcoded Exposure Adjustment

	float ExposureBias = 2.0f;
	RBVector3 curr = _tonemap(ExposureBias*texColor);
	RBVector3 vv(W,W,W);
	float whiteScale = 1.0f / _tonemap(vv).x;
	RBVector3 color = curr*whiteScale;
	//非纹理不需要gama矫正
	c.r = color.x;
	c.g = color.y;
	c.b = color.z;
	c.a = 1.f;
	
}

RBVector4 World::shade(TraceData& _trace_data)
{
	static bool l = true;

	RBVector3 light_dir(-1,1,-1);
	light_dir.normalize();

	RBColorf light_color(0.7,0.7,0.7,1.0);
	RBVector3 abm(0.2,0.2,0.22);

	Ray* ray = _trace_data.cur_ray;

	RBVector3 ip = ray->o + ray->direction*_trace_data.tmin;
	SphereObject* geo = (SphereObject*)_trace_data.nearest_geo;
	RBVector3 normal = geo->get_normal(ip);
	normal.normalize();
	//原点在原点
	RBVector3 view = -ip;
	view.z -= 1;
	view.normalize();

	/*
	RBVector4 res;
	if (l)
	{
		l = false;
		RBVector3 r = (1 + RBVector3::dot_product(view, normal))*normal - view;
		r.normalize();
		Ray ray;
		ray.o = ip;
		ray.direction = r;
		trace_ray(ray);
		_trace_data
	}
	*/

	RBVector4 occ = geo->shade(normal, light_dir, view);
	occ += abm*((PhongMat*)geo->mat)->cd;

	_trace_data.color = occ;


	return occ;
}

RBColorf World::trace_ray(Ray& ray, TraceData& trace_data,int dep)
{
	TraceData _trace_data = trace_data;
	int d = dep;

	if (d >= max_depth)
	{
		return RBColorf::black;
	}

	bool b = false;
	float tmin = MAX_F;
	_ObjectList::iterator it = _objects.begin();
	for (; it != _objects.end(); ++it)
	{

		b = (*it)->hit(ray, _trace_data)||b;
		if (ray.t < tmin)
		{
			_trace_data.tmin = tmin = ray.t;
			_trace_data.nearest_geo = *it;
			_trace_data.cur_ray = &ray;
		}
	}
	ray.t = MAX_F;
	if (b)
	{
		RBVector3 ip = ray.o + ray.direction*_trace_data.tmin;
		SphereObject* geo = (SphereObject*)_trace_data.nearest_geo;
		RBVector3 normal = geo->get_normal(ip);
		normal.normalize();
		RBVector3 rd = -ray.direction.get_normalized();
		RBVector3 rrd = normal*RBVector3::dot_product(normal, rd) * 2-rd;
		rrd.normalize();
		Ray rr; rr.direction = rrd; rr.o = ip;
		RBColorf ic = trace_ray(rr, _trace_data,++d);

		

			

		RBColorf oc = shade(_trace_data) + ic;
		return oc;
	}
	else
	{
		return RBColorf::black;
	}
}

void World::out_put()
{
	int size = 800;
	/*
	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			std::cout << (unsigned int)_out_image[i * size * 4 + j * 4] << " "
				<< (unsigned int)_out_image[i * size * 4 + j * 4 + 1] << " "
				<< (unsigned int)_out_image[i * size * 4 + j * 4 + 2] << " "
				<< (unsigned int)_out_image[i * size * 4 + j * 4 + 3] << " " << std::endl;
		}
	}
	*/

	ClImage* i = new ClImage();
	i->channels = 3;
	i->height = size;
	i->width = size;
	i->imageData = _out_image;
	bool flag = clSaveImage("c:/result1.bmp", i);
	if (flag)
	{
		printf("save ok... \n");
	}
}
