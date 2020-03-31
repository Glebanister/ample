#include <vector>

#include "EditorIO.h"
#include "Exception.h"
#include "WorldObject2d.h"
#include "RegularPolygon.h"

namespace ample::filing
{

std::string openJSONfile(const std::string &nameFile)
{
    std::ifstream inFile(nameFile);
    if (!inFile)
    {
        throw exception::Exception(exception::exId::FILE_READ,
                                   exception::exType::CRITICAL);
    }
    std::stringstream jsonDocumentBuffer;
    std::string inputLine;
    while (std::getline(inFile, inputLine))
    {
        jsonDocumentBuffer << inputLine << "\n";
    }
    inFile.close();
    return jsonDocumentBuffer.str();
}

EditorIO::EditorIO(const std::string &jsonStr_)
        : jsonStr(jsonStr_)
{}

std::string EditorIO::getString() const
{
    return jsonStr;
}

void EditorIO::JSONreader(const std::string &nameField, int &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetInt();
}


void EditorIO::JSONreader(const std::string &nameField, float &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetFloat();
}

void EditorIO::JSONreader(const std::string &nameField, std::string &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj = itr->value.GetString();
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<float> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj.x = itr->value[0].GetFloat();
    obj.y = itr->value[1].GetFloat();
}

void EditorIO::JSONreader(const std::string &nameField, std::vector<ample::graphics::Vector2d<float>> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    for (size_t i = 0; i < itr->value.Size(); ++i)
    {
        obj.push_back({itr->value[i][0].GetFloat(), itr->value[i][1].GetFloat()});
    }
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<int> &obj)
{
    rapidjson::Document doc;
    doc.SetObject();
    doc.Parse(jsonStr.c_str());
    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());

    obj.x = itr->value[0].GetInt();
    obj.y = itr->value[1].GetInt();
}

void EditorIO::JSONreader(const std::string &nameField, ample::graphics::channelMode &obj)
{
    std::string temp = "";
    JSONreader(nameField, temp);

    if (temp == "RGB")
    {
        obj = ample::graphics::channelMode::RGB;
    }
    else if (temp == "RGBA")
    {
        obj = ample::graphics::channelMode::RGBA;
    }
}

//void EditorIO::JSONreader(const std::string &nameField, ample::graphics::normalsMode &obj)
//{
//    std::string temp = "";
//    JSONreader(nameField, temp);
//
//    if (temp == "SINGLE")
//    {
//        obj = ample::graphics::normalsMode::SINGLE;
//    }
//    else if (temp == "VERTEX")
//    {
//        obj = ample::graphics::normalsMode::VERTEX;
//    }
//    else if (temp == "FACE")
//    {
//        obj = ample::graphics::normalsMode::FACE;
//    }
//}
//
//void EditorIO::JSONreader(const std::string &nameField, ample::graphics::textureMode &obj)
//{
//    std::string temp = "";
//    JSONreader(nameField, temp);
//
//    if (temp == "TILE")
//    {
//        obj = ample::graphics::textureMode::TILE;
//    }
//    else if (temp == "STRETCH")
//    {
//        obj = ample::graphics::textureMode::STRETCH;
//    }
//}
//
//void EditorIO::JSONreader(const std::string &nameField, ample::graphics::Vector2d<ample::graphics::textureMode> &obj)
//{
//    rapidjson::Document doc;
//    doc.SetObject();
//    doc.Parse(jsonStr.c_str());
//    rapidjson::Value::ConstMemberIterator itr = doc.FindMember(nameField.c_str());
//
//    std::string strX = itr->value[0].GetString();
//    std::string strY = itr->value[1].GetString();
//
//    if (strX == "TILE")
//    {
//        obj.x = ample::graphics::textureMode::TILE;
//    }
//    else if (strX == "STRETCH")
//    {
//        obj.x = ample::graphics::textureMode::STRETCH;
//    }
//
//    if (strY == "TILE")
//    {
//        obj.y = ample::graphics::textureMode::TILE;
//    }
//    else if (strY == "STRETCH")
//    {
//        obj.y = ample::graphics::textureMode::STRETCH;
//    }
//}

//ample::graphics::GraphicalObject2dRaw EditorIO::loadGO2d()
//{
//    std::vector<graphics::Vector2d<float>> graphicalShape;
//    JSONreader("graphicalShape", graphicalShape);
//
//
//    float depth;
//    JSONreader("depth", depth);
//
//
//    float z;
//    JSONreader("z", z);
//
//
//    std::string faceTexturePath;
//    JSONreader("faceTexturePath", faceTexturePath);
//
//
//    graphics::Vector2d<int> faceTextureSize;
//    JSONreader("faceTextureSize", faceTextureSize);
//
//
//    graphics::Vector2d<int> faceTexturePos;
//    JSONreader("faceTexturePos", faceTexturePos);
//
//
//    graphics::Vector2d<graphics::textureMode> faceTextureMode {graphics::textureMode::STRETCH,
//                                                               graphics::textureMode::STRETCH};
//    JSONreader("faceTextureMode", faceTextureMode);
//
//
//    graphics::channelMode faceChannelMode = graphics::channelMode::RGB;
//    JSONreader("faceChannelMode", faceChannelMode);
//
//
//    std::string sideTexturePath;
//    JSONreader("sideTexturePath", sideTexturePath);
//
//
//    graphics::Vector2d<int> sideTextureSize;
//    JSONreader("sideTextureSize", sideTextureSize);
//
//
//    graphics::Vector2d<int> sideTexturePos;
//    JSONreader("sideTexturePos", sideTexturePos);
//
//
//    graphics::Vector2d<graphics::textureMode> sideTextureMode {graphics::textureMode::STRETCH,
//                                                               graphics::textureMode::STRETCH};
//    JSONreader("sideTextureMode", sideTextureMode);
//
//
//    graphics::normalsMode sideNormalsMode = graphics::normalsMode::FACE;
//    JSONreader("sideNormalsMode", sideNormalsMode);
//
//
//    graphics::channelMode sideChannelMode = graphics::channelMode::RGB;
//    JSONreader("sideChannelMode", sideChannelMode);
//
//
//    graphics::GraphicalObject2dRaw rawObj {
//            graphicalShape,
//            depth,
//            z,
//            faceTexturePath,
//            faceTextureSize,
//            faceTexturePos,
//            faceTextureMode,
//            faceChannelMode,
//            sideTexturePath,
//            sideTextureSize,
//            sideTexturePos,
//            sideTextureMode,
//            sideChannelMode,
//            sideNormalsMode};
//    return rawObj;
//}

} //namespace ample::filing