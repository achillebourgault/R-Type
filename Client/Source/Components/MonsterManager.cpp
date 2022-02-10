/*
** EPITECH PROJECT, 2024
** MonsterManager.cpp
** File description:
** Created by Leo Fabre
*/
#include "MonsterManager.hpp"
#include "MonsterComp.hpp"
#include "ECS/Entity.hpp"

void MonsterManager::SpawnMonster(MonsterInfo info)
{
    auto &newMonster =
        entity->_mgr.addEntity("monster" + std::to_string(info.monsterID));
    newMonster.addComponent<MonsterComp>(info.monsterType, info.monsterID);
    newMonster.getComponent<TransformComp>().position = sf::Vector2f(
        std::get<0>(info.monsterPos),
        std::get<1>(info.monsterPos)
    );
}

void MonsterManager::applyState(GameState state)
{
    auto MonsterEntities = entity->_mgr.getEntitiesInGroup(Monsters);
    //update existing monsters
    //for all existing monster entities, apply state.
    for (auto ent: MonsterEntities) {
        auto &monster_comp = ent->getComponent<MonsterComp>();
        bool foundInfo = false;
        for (auto &monsterInfo: state.monsters) {
            //if this state.info is current monster_comp's info
            if (monsterInfo.monsterID == monster_comp.id) {
                foundInfo = true;
                //apply state from info
                auto &tc = ent->getComponent<TransformComp>();
                tc.position.x = std::get<0>(monsterInfo.monsterPos);
                tc.position.y = std::get<1>(monsterInfo.monsterPos);
                if (monsterInfo.shotMissile) {
                    monster_comp.ShootMonsterMissile(monsterInfo);
                }
                break;
            }
        }
        //if no state was found for monster entity, destroy it.
        if (!foundInfo) {
            std::cout << "monsterManager : destroying monster "
                << ent->getName() << std::endl;
            ent->destroy();
        }
    }
}
