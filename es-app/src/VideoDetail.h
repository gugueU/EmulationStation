#pragma once
#ifndef ES_APP_VIDEO_DETAIL_H
#define ES_APP_VIDEO_DETAIL_H

#include <components/ImageComponent.h>
#include "components/DateTimeComponent.h"
#include "components/RatingComponent.h"
#include "components/ScrollableContainer.h"
#include "FileData.h"

class VideoComponent;

class VideoDetail : public GuiComponent{

public:
    VideoDetail(Window *window, FileData *root);

    ~VideoDetail() override;

    void render(const Transform4x4f &parentTrans) override;

    void update(int deltaTime) override;


private:
    ImageComponent mMarquee;
    VideoComponent *mVideo;
    ImageComponent mImage;
    ImageComponent mFavIcon;
    FileData *mGame;

    RatingComponent mRating;
    DateTimeComponent mReleaseDate;
    TextComponent mDeveloper;
    TextComponent mPublisher;
    TextComponent mGenre;
    TextComponent mPlayers;
    DateTimeComponent mLastPlayed;
    TextComponent mPlayCount;
    TextComponent mName;
    TextComponent mPlateform;

    std::vector<TextComponent *> getMDLabels();

    std::vector<GuiComponent *> getMDValues();

    ScrollableContainer mDescContainer;
    TextComponent mDescription;

};

#endif // ES_APP_VIDEO_DETAIL_H