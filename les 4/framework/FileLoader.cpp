#include "FileLoader.h"

std::vector<std::string> FileLoader::SplitString(const std::string& string, char delim) {
    std::vector<std::string> result;
    std::stringstream stream(string);
    std::string split;

    while (std::getline(stream, split, delim)) {
        result.push_back(split);
    }

    return result;
}

std::map<int, Object> FileLoader::LoadObjects(const std::string& filename) {
    std::ifstream stream(filename.c_str());
    std::string line;

    std::map<int, glm::vec3> vertices;
    std::map<int, Face> faces;
    std::map<int, Object> objects;

    if (stream.is_open()) {
        while (stream.good()) {
            std::getline(stream, line);
            auto tokens = SplitString(line, ' ');
            if (!tokens.empty() && tokens[0].size() == 1) {
                char type = tokens[0][0];
                switch (type) {
                    case 'v': {
                        int index = std::stoi(tokens[1]);
                        glm::vec3 vertex(std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]));
                        vertices[index] = vertex;
                        break;
                    }
                    case 'f': {
                        int index = std::stoi(tokens[1]);
                        std::vector<glm::vec3> faceVertices = {vertices[std::stoi(tokens[2])],
                                                               vertices[std::stoi(tokens[3])],
                                                               vertices[std::stoi(tokens[4])]};
                        Face face;
                        for (int i = 0; i < 3; i++) {
                            face.vertices[i] = glm::vec4(faceVertices[i], 1.0f);
                        }                                       
                        faces[index] = face;
                        break;
                    }
                    case 'o': {
                        int index = std::stoi(tokens[1]);
                        Object object;
                        for (size_t i = 2; i < tokens.size(); i++) {
                            int faceId = std::stoi(tokens[i]);
                            if (faces.find(faceId) != faces.end()) {
                                object.faces.push_back(faces[faceId]);
                            }
                        }
                        objects[index] = object;
                        break;
                    }
                    default:
                        break;
                }
            } else {
                std::cerr << "unknown symbol";
            }
        }
    }

    return objects;
}

std::map<int, Bezier> FileLoader::LoadCurves(const std::string &filename) {
    std::ifstream stream(filename.c_str());
    std::string line;

    std::map<int, glm::vec3> vertices;
    std::map<int, Bezier> curves;

    if (stream.is_open()) {
        while (stream.good()) {
            std::getline(stream, line);
            auto tokens = SplitString(line, ' ');
            if (!tokens.empty() && tokens[0].size() == 1) {
                char type = tokens[0][0];
                switch (type) {
                    case 'v': {
                        int index = std::stoi(tokens[1]);
                        glm::vec3 vertex(std::stof(tokens[2]), std::stof(tokens[3]), std::stof(tokens[4]));
                        vertices[index] = vertex;
                        break;
                    }
                    case 'b': {
                        int index = std::stoi(tokens[1]);
                        auto method = static_cast<Bezier::IterationMethod>(std::stoi(tokens[2]));
                        int steps = std::stoi(tokens[3]);
                        auto tokensAfter = SplitString(SplitString(line, '|')[1], ' ');
                        Bezier bezier(
                                vertices[std::stoi(tokensAfter[0])],
                                vertices[std::stoi(tokensAfter[1])],
                                vertices[std::stoi(tokensAfter[2])],
                                vertices[std::stoi(tokensAfter[3])],
                                steps, method);
                        curves[index] = bezier;
                        break;
                    }
                    default:
                        break;
                }
            } else {
                std::cerr << "unknown symbol";
            }
        }
    }

    return curves;
}
