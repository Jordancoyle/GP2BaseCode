#ifndef _CAMERA_H
#define _CAMERA_H

#include "common.h"

class CameraObject
{
public:
	CameraObject();
	~CameraObject();

	void Update();

	mat4& getProjMatrix()
	{
		return m_ProjMatrix;
	}
	mat4& getViewMatrix()
	{
		return m_ViewMatrix;
	}
	vec3& getCameraPosition()
	{
		return m_CameraPosition;
	}
	vec3& getLookCenter()
	{
		return m_LookCenter;
	}
	vec3& getLookUp()
	{
		return m_LookUp;
	}
	float getFovy()
	{
		return m_Fovy;
	}
	float getAspect()
	{
		return m_Aspect;
	}
	float getNear()
	{
		return m_Near;
	}
	float getFar()
	{
		return m_Far;
	}

	void setCameraPosition(vec3 cameraPosition)
	{
		m_CameraPosition = cameraPosition;
	}
	void setLookCenter(vec3 lookCenter)
	{
		m_LookCenter = lookCenter;
	}
	void setLookUp(vec3 lookUp)
	{
		m_LookUp = lookUp;
	}
	void setFovy(float fovy)
	{
		m_Fovy = fovy;
	}
	void setAspect(float aspect)
	{
		m_Aspect = aspect;
	}
	void setNear(float n)
	{
		m_Near = n;
	}
	void setFar(float f)
	{
		m_Far = f;
	}
private:
	mat4 m_ProjMatrix;
	mat4 m_ViewMatrix;

	vec3 m_CameraPosition;
	vec3 m_LookCenter;
	vec3 m_LookUp;

	float m_Fovy;
	float m_Aspect;
	float m_Near;
	float m_Far;
protected:
};

#endif