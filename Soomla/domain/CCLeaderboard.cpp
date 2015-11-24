//
// Created by Eugene Butusov on 23/11/15.
// Copyright (c) 2015 SOOMLA. All rights reserved.
//

#include "CCLeaderboard.h"

soomla::CCLeaderboard *soomla::CCLeaderboard::create(cocos2d::__String *id, cocos2d::__String *provider) {

    CCLeaderboard *ret = new CCLeaderboard();
    if (ret->init(id, provider)) {
        ret->autorelease();
    }
    else {
        CC_SAFE_DELETE(ret);
    }
    return ret;
}

bool soomla::CCLeaderboard::init(cocos2d::__String *id, cocos2d::__String *provider) {
    
    setId(id);
    setProvider(provider);
    
    return true;
}


bool soomla::CCLeaderboard::initWithDictionary(cocos2d::__Dictionary *dict) {
    CCSoomlaEntity::initWithDictionary(dict);
    fillProviderFromDict(dict);

    return true;
}

cocos2d::__Dictionary *soomla::CCLeaderboard::toDictionary() {
    cocos2d::__Dictionary* dict = CCSoomlaEntity::toDictionary();

    putProviderToDict(dict);

    return dict;
}

const char * soomla::CCLeaderboard::getType() const {
    return "Leaderboard";
}

soomla::CCLeaderboard::~CCLeaderboard() {
    CC_SAFE_RELEASE(mProvider);
}
