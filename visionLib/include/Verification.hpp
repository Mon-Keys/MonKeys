#ifndef VISION_VERIFICATION_HPP
#define VISION_VERIFICATION_HPP

class Verification {
public:
    virtual void open() = 0;
    virtual void establishConnection(const char *url) = 0;
};

#endif //VISION_VERIFICATION_HPP
