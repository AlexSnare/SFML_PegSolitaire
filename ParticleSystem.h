#pragma once

#include <SFML/Graphics.hpp>

class ParticleSystem
  : public sf::Drawable
  , public sf::Transformable
{
public:
  ParticleSystem(unsigned int count, const sf::Vector2u winSize)
    : m_particles(count)
    , m_vertices(sf::Points, count)
    , m_lifetime(sf::seconds(0.00001f))
    , m_emitter(0.f, 0.f)
    , m_winSize(winSize)
  {}

  void setEmitter(sf::Vector2f position) { m_emitter = position; }

  void update(sf::Time elapsed)
  {
    for (std::size_t i = 0; i < m_particles.size(); ++i) {
      // update the particle lifetime
      Particle& p = m_particles[i];
      p.lifetime -= elapsed;

      // if the particle is dead, respawn it
      if (p.lifetime <= sf::Time::Zero)
        resetParticle(i);

      if ((m_vertices[i].position.x < 0) ||
          (m_vertices[i].position.x > m_winSize.x) ||
          (m_vertices[i].position.y < 0) ||
          (m_vertices[i].position.y > m_winSize.y))
        resetParticle(i);

      // update the position of the corresponding vertex
      m_vertices[i].position += p.velocity * elapsed.asSeconds();

      // update the alpha (transparency) of the particle according to its
      // lifetime
      float ratio = p.lifetime.asSeconds() / m_lifetime.asSeconds();

      // m_vertices[i].color.a = static_cast<sf::Uint8>(ratio * 255); //
    }
  }

private:
  virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
  {
    // apply the transform
    states.transform *= getTransform();

    // our particles don't use a texture
    states.texture = NULL;

    // draw the vertex array
    target.draw(m_vertices, states);
  }

private:
  struct Particle
  {
    sf::Vector2f velocity;
    sf::Time lifetime;
  };

  void resetParticle(std::size_t index)
  {
    // give a random velocity and lifetime to the particle
    float angle = ((std::rand() % 3600) / 10.f) * 3.14f / 180.f;
    float speed = (std::rand() % 100) + 100.f;
    m_particles[index].velocity =
      sf::Vector2f(std::cos(angle) * speed, std::sin(angle) * speed);
    m_particles[index].lifetime = sf::milliseconds((std::rand() % 4000) + 4000);

    // reset the position of the corresponding vertex
    float startRadius = std::min(m_winSize.x, m_winSize.y) / 3.f;

    m_vertices[index].position =
      m_emitter + sf::Vector2f(std::cos(angle) * startRadius,
                               std::sin(angle) * startRadius);

    float s = (speed - 100.f) / 100.f;

    m_vertices[index].color.r = static_cast<sf::Uint8>(255 * s); // 166
    m_vertices[index].color.g = static_cast<sf::Uint8>(255);   // 127
    m_vertices[index].color.b = static_cast<sf::Uint8>(255 - 255 * s);   // 255
  }

  std::vector<Particle> m_particles;
  sf::VertexArray m_vertices;
  sf::Time m_lifetime;
  sf::Vector2f m_emitter;
  sf::Vector2u m_winSize;
};