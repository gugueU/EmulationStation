#include "VideoDetail.h"

#include "animations/LambdaAnimation.h"

#ifdef _RPI_
#include "components/VideoPlayerComponent.h"
#endif

#include "components/VideoVlcComponent.h"
#include "utils/FileSystemUtil.h"
#include "views/ViewController.h"
#include "SystemData.h"

#ifdef _RPI_
#include "Settings.h"
#endif

VideoDetail::VideoDetail(Window *window, FileData *game) :
        GuiComponent(window),
        mDescContainer(window), mDescription(window),
        mMarquee(window),
        mImage(window),
        mFavIcon(window),
        mVideo(nullptr),
        mGame(game),
        mPlateform(window),

        mRating(window), mReleaseDate(window), mDeveloper(window), mPublisher(window),
        mGenre(window), mPlayers(window), mLastPlayed(window), mPlayCount(window),
        mName(window)
        {

            std::shared_ptr<Font> FONT_SMALL = Font::get(FONT_SIZE_MEDIUM);
            std::shared_ptr<Font> FONT_MINI = Font::get(FONT_SIZE_SMALL);
            const Vector2f textSizeSmall = Vector2f((float) Renderer::getScreenWidth() * 0.20f, FONT_SMALL->getHeight());
            const Vector2f textSizeMini = Vector2f((float) Renderer::getScreenWidth() * 0.20f, FONT_MINI->getHeight());
            const float interline = (float) Renderer::getScreenHeight() * .004f;

            mImage.setImage(mGame->getImagePath());
            mImage.setOrigin(0.5f, 0.5f);
            mImage.setPosition((float) Renderer::getScreenWidth() * 0.125f, (float) Renderer::getScreenHeight() * 0.25f);
            mImage.setMaxSize((float) Renderer::getScreenWidth() * 0.20f,
                              (float) Renderer::getScreenHeight() * 0.45f);
            addChild(&mImage);

            std::string name = mGame->metadata.get("name");
            name = name.substr(0, name.find('['));
            mName.setFont(FONT_SMALL);
            mName.setUppercase(true);
            mName.setValue(name);
            mName.setColor(0xFFFFFFFF);
            mName.setVerticalAlignment(ALIGN_LEFT);
            mName.setOrigin(0.0f, 0.0f);
            mName.setPosition((float) Renderer::getScreenWidth() * 0.02f, (float) Renderer::getScreenHeight() * 0.55f);
            mName.setSize(textSizeSmall);
            addChild(&mName);

            mReleaseDate.setValue(mGame->metadata.get("releasedate"));
            mReleaseDate.setFont(FONT_MINI);
            mReleaseDate.setOrigin(0.f, 0.0f);
            mReleaseDate.setSize(textSizeMini);
            mReleaseDate.setColor(0xFFFFFFFF);
            mReleaseDate.setPosition((float) Renderer::getScreenWidth() * 0.02f,
                                     mName.getPosition().y() + (float) Renderer::getScreenHeight() * 0.1f);
            mReleaseDate.setFormat("%Y");
            addChild(&mReleaseDate);

            mPlateform.setValue(game->getSystem()->getFullName());
            mPlateform.setOrigin(0.f, 0.0f);
            mPlateform.setFont(FONT_MINI);
            mPlateform.setSize(textSizeMini);
            mPlateform.setColor(0xFFFFFFFF);
            mPlateform.setPosition((float) Renderer::getScreenWidth() * 0.02f,
                                   mReleaseDate.getPosition().y() +
                                   mReleaseDate.getSize().y() + interline);
            addChild(&mPlateform);

            mDeveloper.setValue(mGame->metadata.get("developer"));
            mDeveloper.setFont(FONT_MINI);
            mDeveloper.setOrigin(0.f, 0.0f);
            mDeveloper.setSize(textSizeMini);
            mDeveloper.setColor(0xFFFFFFFF);
            mDeveloper.setPosition((float) Renderer::getScreenWidth() * 0.02f,
                                   mPlateform.getPosition().y() +
                                   mPlateform.getSize().y() + interline);
            addChild(&mDeveloper);

            mFavIcon.setImage(":/star_fav_icon.png");
            mFavIcon.setPosition((float) Renderer::getScreenWidth() * 0.02f,
                                 mDeveloper.getPosition().y() +
                                 mDeveloper.getSize().y() + interline);
            mFavIcon.setSize(32, 32);

            // Create the correct type of video window
#ifdef _RPI_
    if (Settings::getInstance()->getBool("VideoOmxPlayer"))
        mVideo = new VideoPlayerComponent(window, "");
    else
        mVideo = new VideoVlcComponent(window, "");
#else
    mVideo = new VideoVlcComponent(window, "");
#endif

    mVideo->topWindow(true);
    mVideo->setOrigin(1.0f, 0.5f);
    mVideo->setPosition((float) Renderer::getScreenWidth()-20, (float) Renderer::getScreenHeight() * 0.5f);
    mVideo->setMaxSize((float) Renderer::getScreenWidth() * 0.75f-20, (float) Renderer::getScreenHeight()-20);
    mVideo->setVideo(mGame->getVideoPath());
    mVideo->setScreensaverMode(true);
    mVideo->onShow();
    addChild(mVideo);

}

VideoDetail::~VideoDetail() {
    mGame = nullptr;
    delete mVideo;
}

void VideoDetail::render(const Transform4x4f &parentTrans) {
    Renderer::setMatrix(Transform4x4f::Identity());

    // Render white background (meta)
//    Renderer::drawRect(0.0f, (float) Renderer::getScreenHeight() * 0.5f, (float) Renderer::getScreenWidth() * 0.25f,
//                       (float) Renderer::getScreenHeight() * 0.5f, 0xFFFFFFFF, 0xFFFFFFFF);

    // Render grey square background (cover)
//    R

    if (mGame->metadata.get("favorite") == "true") {
        mFavIcon.render(parentTrans);
    }
    renderChildren(parentTrans);
}

void VideoDetail::update(int deltaTime) {
    mVideo->update(deltaTime);
}
