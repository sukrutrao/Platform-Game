#ifndef ENUMERATOR_H
#define ENUMERATOR_H

namespace enumerator
{
    enum class State { MOVING_RIGHT, MOVING_LEFT, STOP_RIGHT, STOP_LEFT, DEAD_RIGHT, DEAD_LEFT };
    enum class JumpingState { IS_JUMPING, IS_NOT_JUMPING };
    enum class Identity { SERVER, CLIENT };
    enum class ObjectType { PLAYER, ENEMY };
}

#endif // ENUMERATOR_H
