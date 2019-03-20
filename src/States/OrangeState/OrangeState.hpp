#ifndef POPHEAD_STATES_ORANGESTATE_ORANGESTATE_H
#define POPHEAD_STATES_ORANGESTATE_ORANGESTATE_H

#include "States/State.hpp"
#include "Base/GameData.hpp"

namespace PopHead{
namespace States{


class OrangeState : public State
{
public:
    OrangeState(Base::GameData *gameData);

    void input() override;
    void update(sf::Time delta) override;

private:
    Base::GameData *gameData;
};


}}

#endif // POPHEAD_STATES_ORANGESTATE_ORANGESTATE_H
