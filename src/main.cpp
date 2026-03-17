#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        auto btn = CCMenuItemSpriteExtra::create(
            CCSprite::create("GJ_plusBtn_001.png"),
            this,
            menu_selector(MyMenuLayer::onDiscord)
        );

        btn->setPosition({0, -100});

        this->getChildByID("bottom-menu")->addChild(btn);

        return true;
    }

    void onDiscord(CCObject*) {
        log::info("Button clicked");
    }
};
