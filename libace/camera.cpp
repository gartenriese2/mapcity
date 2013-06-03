/*
*
*   Copyright (c) 2013, Jan Doerntlein.
*   All rights reserved.
*
*/

#include "camera.h"

namespace ace {

// static initializers
int Camera::s_nextId = 0;
int Camera::s_active = 0;
std::vector<Camera*> Camera::s_camContainer;

// global function: get camera by its id
Camera* Camera::get( int id ) {
    Camera* p;
    for( auto c : s_camContainer ) {
        if( c->getId() == id ) {
            p = c;
            return p;
        }
    }
    return p;
}

// global function: get currently active camera
Camera* Camera::getActive() {
    Camera* p;
    for( auto c : s_camContainer ) {
        if( c->getId() == s_active ) {
            p = c;
            return p;
        }
    }
    return p;
}

void Camera::setActive() {
    s_active = m_id;
}

// constructors
Camera::Camera( glm::vec3& pos, glm::vec3& dir, glm::vec3& up, float fov,
                float aspect, float near, float far ) {
    
    // fill static camera container
    m_id     = s_nextId++;
    setActive();
    s_camContainer.push_back( this );

    // perspective params
    m_pos  = pos;
    m_dir  = dir;
    m_up   = up;
    m_fov  = fov;
    m_near = near;
    m_far  = far;
    m_aspectratio = aspect;

    // orthographic params
    m_left   = 0;
    m_right  = 0;
    m_bottom = 0;
    m_top    = 0; 

    // init matrices
    m_view       = glm::mat4();
    m_projection = glm::mat4();
    m_model      = glm::mat4();

    // create camera
    Perspective();
    Lookat();

    m_isPerspectiveCam = true;
}

Camera::Camera( glm::vec3& pos, glm::vec3& dir, glm::vec3& up, 
    float left, float right, float bottom, float top, float near, float far ) {

    // fill static camera container
    m_id = s_nextId++;
    s_camContainer.push_back( this );

    // perspective params
    m_pos  = pos;
    m_dir  = dir;
    m_up   = up;
    m_near = near;
    m_far  = far;
    m_aspectratio = 0;
    m_fov  = 0;

    // orthographic cam
    m_left   = left;
    m_right  = right;
    m_bottom = bottom;
    m_top    = top;

    // init matrices
    m_view       = glm::mat4();
    m_projection = glm::mat4();
    m_model      = glm::mat4();

    // create camera
    Ortho();
    Lookat();

    m_isPerspectiveCam = false;
} 

void Camera::update() {
    Lookat();
}

glm::mat4& Camera::getProjectionMatrix() {
    return m_projection;
}

glm::mat4& Camera::getViewMatrix() {
    return m_view;
}

glm::mat4& Camera::getModelMatrix() {
    return m_model;
}

void Camera::Lookat() {
    m_view  = glm::lookAt( m_pos, m_pos + m_dir, m_up );
}

void Camera::Perspective() {
    m_projection = glm::perspective( m_fov, m_aspectratio, m_near, m_far );
}

void Camera::Ortho() {
    m_projection = glm::ortho( m_left, m_right, m_bottom, m_top, m_near, m_far );
}

void Camera::move( float v ) {
    m_pos += v * m_dir;
    update();
}

void Camera::strafe( float dir ) {
    m_pos += dir * glm::cross( m_dir, m_up );
    update();
}

void Camera::setPos( glm::vec3& pos ) {
    m_pos = pos;
    update();
}

void Camera::setDir( glm::vec3& dir ) {
    m_dir = dir;
    glm::normalize( m_dir );
    update();
}

void Camera::rotateX( float angle ) {
    m_dir = glm::rotate( m_dir, angle, glm::vec3( 1, 0, 0 ) );
    update();
}

void Camera::rotateY( float angle ) {
    m_dir = glm::rotate( m_dir, angle, glm::vec3( 0, 1, 0 ) );
    update();
}

void Camera::rotateZ( float angle ) {
    m_dir = glm::rotate( m_dir, angle, glm::vec3( 0, 0, 1 ) );
    update();
}

void Camera::yaw( float angle ) {
    m_dir = glm::rotate( m_dir, angle, glm::cross( m_up, m_dir ) );
    update();
}

void Camera::pitch( float angle ) {
    m_dir = glm::rotate( m_dir, angle, glm::vec3( 0, 1, 0 ) );
    update();
}

void Camera::roll( float angle ) {
    m_dir = glm::rotate( m_dir, angle, m_dir );
    update();
}

Camera::~Camera() {
    
}

}
