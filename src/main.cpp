#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>

using namespace geode::prelude;

class $modify(RTXPlayLayer, PlayLayer) {
    struct Fields {
        CCDrawNode* glow = nullptr;
    };

    void setupHasCompleted() {
        PlayLayer::setupHasCompleted();
        if (!Mod::get()->getSettingValue<bool>("enabled")) return;

        auto glow = CCDrawNode::create();
        glow->setBlendFunc({GL_SRC_ALPHA, GL_ONE});
        glow->setZOrder(1000);
        m_objectLayer->addChild(glow);
        m_fields->glow = glow;
    }

    void postUpdate(float dt) {
        PlayLayer::postUpdate(dt);

        auto glow = m_fields->glow;
        if (!glow || !m_player1) return;

        float k = static_cast<float>(
            Mod::get()->getSettingValue<double>("intensity"));

        auto c = GameManager::get()->colorForIdx(
            GameManager::get()->getPlayerColor());
        auto pos = m_player1->getPosition();

        glow->clear();
        for (int i = 0; i < 14; i++) {
            float radius = 25.f + i * 14.f;
            float alpha = 0.05f * k * (1.f - i / 14.f);
            glow->drawDot(pos, radius,
                ccc4f(c.r / 255.f, c.g / 255.f, c.b / 255.f, alpha));
        }
    }
};
