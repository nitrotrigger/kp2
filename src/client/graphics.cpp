#include "graphics.hpp"

#include "sdl.hpp"
#include "assert.hpp"
#include "ui.hpp"
#include "texture.hpp"
#include "events.hpp"

#include <iostream>
#include <cstdlib>
#include <GL/glew.h>

void Graphics::printVideoInfo()
{
	Vector2D displaysize=getDisplaySize();

	std::cout<<"Video mode: "<<displaysize.getX()<<"x"<<displaysize.getY()<<"x"<<getBitsPerPixel();
	
	if(isDoubleBuffered())
		std::cout<<" doublebuffered";
	
	if(isVsynced())
		std::cout<<" vsynced";
	
	if(isFullScreen())
		std::cout<<" fullscreen";

	std::cout<<std::endl;
}

float Graphics::getAspectRatio()
{
	Vector2D displaysize=getDisplaySize();

	return displaysize.getX()/displaysize.getY();
}

void Graphics::enterGuiMode()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();	
	glOrtho(0,1,1,0,0,1);
	glMatrixMode(GL_MODELVIEW);
}

void Graphics::exitGuiMode()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

int Graphics::setVideoMode(int width,int height,int bpp,bool fullscreen,bool vsync,bool doublebuffer)
{
	if (SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER,doublebuffer) == -1)
		std::cerr << "SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER," << doublebuffer << ") returned -1" << std::endl;

	if (SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL,vsync) == -1)
		std::cout << "SDL_GL_SetAttribute(SDL_GL_SWAP_CONTROL," << vsync << ") returned -1" << std::endl;

	int flags=SDL_OPENGL;

	if(fullscreen)
		flags|=SDL_FULLSCREEN;
	
	m_surface = SDL_SetVideoMode(width, height, bpp, flags);

	if(!m_surface)
	{
		std::cerr << "SDL_SetVideoMode(" << width << "," << height << "," << bpp << "," << flags << ") failed: " << SDL_GetError() << std::endl; 	
		return -1;
	}
	
	Vector2D displaysize=getDisplaySize();
	
	glViewport(0,0,displaysize.getX(),displaysize.getY());
	glEnable(GL_TEXTURE_2D);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);

	GLenum retval = glewInit();

	if(retval != GLEW_OK)
	{
		std::cerr<<"glewInit() failed: "<< glewGetErrorString(retval) <<std::endl; 	
		return -1;
	}

	printVideoInfo();
	
	Texture::reuploadTextures();
	
	m_events.resize(*this);
	
	return 0;
}

class Compare
{
	public:
		bool operator() (const Vector2D& lhs, const Vector2D& rhs) const
		{
			if(lhs.getX() == rhs.getX())
				return lhs.getY()<rhs.getY();
			else
				return lhs.getX()<rhs.getX();
		}
};

std::vector<Vector2D> Graphics::getVideoModes()
{
	std::set<Vector2D,Compare> modelist;
	
	SDL_Rect** modes = SDL_ListModes(NULL, SDL_OPENGL|SDL_FULLSCREEN);

	if (modes == (SDL_Rect**)0)
	{
		std::cout<<"No modes available!\n"<<std::endl;
	}

	/* Check if our resolution is restricted */
	if (modes == (SDL_Rect**)-1)
	{
		std::cout<<"All resolutions available.\n"<<std::endl;
	}
	else
	{
		for (int i=0; modes[i]; ++i)
			modelist.insert(Vector2D(modes[i]->w,modes[i]->h));
	}
	
	std::vector<Vector2D> final;
	std::set<Vector2D,Compare>::iterator i;
		
	for(i=modelist.begin();i!=modelist.end();++i)
	{
		final.push_back(*i);
	}	

	return final;
}

bool Graphics::isDoubleBuffered()
{
	int value;

	SDL_GL_GetAttribute(SDL_GL_DOUBLEBUFFER,&value);

	return value;
}

bool Graphics::isVsynced()
{
	int value;

	SDL_GL_GetAttribute(SDL_GL_SWAP_CONTROL,&value);

	return value;
}

bool Graphics::isFullScreen()
{
	return m_surface->flags & SDL_FULLSCREEN;
}

int Graphics::getBitsPerPixel()
{
	return m_surface->format->BitsPerPixel;	
}

void Graphics::resize(Vector2D size)
{
	std::cout<<size<<std::endl;

	setVideoMode(size.getX(),size.getY(),getBitsPerPixel(),isFullScreen(),isVsynced(),isDoubleBuffered());
}

Vector2D Graphics::getDisplaySize()
{
	return Vector2D(m_surface->w,m_surface->h);
}

Graphics::Graphics(Sdl& sdl,Events& events):
	m_sdl(sdl), 
	m_events(events),
	m_surface(0)
{

}

Graphics::~Graphics()
{
	
}

