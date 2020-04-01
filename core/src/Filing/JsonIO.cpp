namespace ample::filing
{

ample::graphics::GraphicalObject2dRaw EditorIO::loadGO2d()
{
    std::vector<graphics::Vector2d<float>> graphicalShape;
    JSONreader("graphicalShape", graphicalShape);


    float depth;
    JSONreader("depth", depth);


    float z;
    JSONreader("z", z);


    std::string faceTexturePath;
    JSONreader("faceTexturePath", faceTexturePath);


    graphics::Vector2d<int> faceTextureSize;
    JSONreader("faceTextureSize", faceTextureSize);


    graphics::Vector2d<int> faceTexturePos;
    JSONreader("faceTexturePos", faceTexturePos);


    graphics::Vector2d<graphics::textureMode> faceTextureMode {graphics::textureMode::STRETCH,
                                                               graphics::textureMode::STRETCH};
    JSONreader("faceTextureMode", faceTextureMode);


    graphics::channelMode faceChannelMode = graphics::channelMode::RGB;
    JSONreader("faceChannelMode", faceChannelMode);


    std::string sideTexturePath;
    JSONreader("sideTexturePath", sideTexturePath);


    graphics::Vector2d<int> sideTextureSize;
    JSONreader("sideTextureSize", sideTextureSize);


    graphics::Vector2d<int> sideTexturePos;
    JSONreader("sideTexturePos", sideTexturePos);


    graphics::Vector2d<graphics::textureMode> sideTextureMode {graphics::textureMode::STRETCH,
                                                               graphics::textureMode::STRETCH};
    JSONreader("sideTextureMode", sideTextureMode);


    graphics::normalsMode sideNormalsMode = graphics::normalsMode::FACE;
    JSONreader("sideNormalsMode", sideNormalsMode);


    graphics::channelMode sideChannelMode = graphics::channelMode::RGB;
    JSONreader("sideChannelMode", sideChannelMode);


    graphics::GraphicalObject2dRaw rawObj {
            graphicalShape,
            depth,
            z,
            faceTexturePath,
            faceTextureSize,
            faceTexturePos,
            faceTextureMode,
            faceChannelMode,
            sideTexturePath,
            sideTextureSize,
            sideTexturePos,
            sideTextureMode,
            sideChannelMode,
            sideNormalsMode};
    return rawObj;
}

} //namespace ample::filing