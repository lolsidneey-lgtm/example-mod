#include <Geode/Geode.hpp>
#include <Geode/modify/MenuLayer.hpp>
#include <cpr/cpr.h>
#include <nlohmann/json.hpp>

using namespace geode::prelude;

class $modify(MyMenuLayer, MenuLayer) {
    bool init() {
        if (!MenuLayer::init()) return false;

        // Create the button
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
        // Step 1: Open Discord OAuth login
        web::openLinkInBrowser(
            "https://discord.com/oauth2/authorize?client_id=1483297716183236729&response_type=code&redirect_uri=http%3A%2F%2Flocalhost%3A8080&scope=guilds+identify"
        );

        // Step 2: Manually paste your code from browser
        std::string code = "Xk1eqYlphjtsz4nCgol2at4Xz4wsdD"; // Example: Xk1eqYlphjtsz4nCgol2at4Xz4wsdD

        // Step 3: Exchange code for token
        auto res = cpr::Post(
            cpr::Url{"https://discord.com/api/oauth2/token"},
            cpr::Payload{
                {"client_id", "1483297716183236729"},
                {"client_secret", "0_ZSuzZl9OqZw8cTT2P7eO99UlCzytmv"},
                {"grant_type", "Xk1eqYlphjtsz4nCgol2at4Xz4wsdD"},
                {"code", code},
                {"redirect_uri", "http://localhost:8080"}
            },
            cpr::Header{{"Content-Type", "application/x-www-form-urlencoded"}}
        );

        log::info("Token response: {}", res.text);

        // Step 4: Parse token and get user info
        try {
            auto json = nlohmann::json::parse(res.text);
            std::string access_token = json["access_token"];

            auto user_res = cpr::Get(
                cpr::Url{"https://discord.com/api/users/@me"},
                cpr::Header{{"Authorization", "Bearer " + access_token}}
            );

            log::info("User info: {}", user_res.text);
        } catch (...) {
            log::info("Failed to parse token or fetch user info. Make sure code is correct.");
        }
    }
};
