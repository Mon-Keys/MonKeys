#include "gtest/gtest.h"
#include "../include/timeCodeGenerator.hpp"

TEST(TimeCodeGeneratorTest, correct_generate_on_one_time_segment) {
    unsigned long PassID = 1;
    unsigned short timeInterval = 30;
    std::string userKey = """
    MIICXAIBAAKBgQCKtyY1BoTzJAPa12Dv0vylkD4Kj4gGQC03I6jnQVi9muVFl+SB
    pKVpkdoW1wv01DGsD2RE/0cw5tWb8ogMychpMR6k7WatSEJxxNv7e2ws7zGp0cE2
    i9YzQrZGYXoxgMTe1de99DeVoQ2QiNWY5K3QV5HnLD6XZ5QD2GOE/VikKQIDAQAB
    AoGABgnlEufev8rwlAVORgJ0VyzJVqJa9JK0pTLbNn4Ew/RLSNVM8Evfm5Hq4ZWp
    ApZ+NxRQdCR8z+cso2ZSf+QE4mawbw+WV3/UPMwTkhEaFMrabfyt23s3xCT1XYt8
    PwRjsMXQ3fw5Jen1lKN3a/BmV1DRWphsuiIV3NzN1qDTEZUCQQDmc9rsF6wNUmKi
    2QhrlwGiR8CiwsTQuzjRwtRWdW0NX66tIrFH25HuCQBpq4FXRILz2P/RgBYTUoub
    ZjEgYTy7AkEAmhfVZiEOItLuLHoZIwWLDGC6Va5692G+KtN01ouWLscoqn1BVjTh
    O7jd6dv9i/NVLoq+0PrA9u/R6JSS4kmmawJAcQUOr8zoP1xRLYZ9H67eSUUhT3Fv
    7uJy+kSvuHs8cVukohqqkRA5IGFfx3MqKq9Z/ddFluxXZ0CLYTocC8JEcwJANarB
    Vu2CR9yguPrZUFo44Fm76+V1zDzNh4rX8XTyHF6eqiovnD+UhkFPgIhu2NQpwaju
    5ke+9wH1YISGV6uA+wJBALsrh9zNW/brxAnQ3wWBZcSPDzAHMuVc238dqNhsN0JA
    wU0seIAZvVJlYk5IohTL7JHapithdwi7h7AZiRDWdvE=
                                """;

    TimeCodeGenerator codegen(userKey, PassID, timeInterval);

    std::string generatedCode = codegen.generateTimeCode();

    std::string precalculatedCode = "NDS0FESKOKOG";

    ASSERT_EQ(generatedCode, precalculatedCode);

}

TEST(TimeCodeGeneratorTest, zeroTimeInterval) {
    unsigned long PassID = 1;
    unsigned short timeInterval = 0;
    std::string userKey = """
    MIICXAIBAAKBgQCKtyY1BoTzJAPa12Dv0vylkD4Kj4gGQC03I6jnQVi9muVFl+SB
    pKVpkdoW1wv01DGsD2RE/0cw5tWb8ogMychpMR6k7WatSEJxxNv7e2ws7zGp0cE2
    i9YzQrZGYXoxgMTe1de99DeVoQ2QiNWY5K3QV5HnLD6XZ5QD2GOE/VikKQIDAQAB
    AoGABgnlEufev8rwlAVORgJ0VyzJVqJa9JK0pTLbNn4Ew/RLSNVM8Evfm5Hq4ZWp
    ApZ+NxRQdCR8z+cso2ZSf+QE4mawbw+WV3/UPMwTkhEaFMrabfyt23s3xCT1XYt8
    PwRjsMXQ3fw5Jen1lKN3a/BmV1DRWphsuiIV3NzN1qDTEZUCQQDmc9rsF6wNUmKi
    2QhrlwGiR8CiwsTQuzjRwtRWdW0NX66tIrFH25HuCQBpq4FXRILz2P/RgBYTUoub
    ZjEgYTy7AkEAmhfVZiEOItLuLHoZIwWLDGC6Va5692G+KtN01ouWLscoqn1BVjTh
    O7jd6dv9i/NVLoq+0PrA9u/R6JSS4kmmawJAcQUOr8zoP1xRLYZ9H67eSUUhT3Fv
    7uJy+kSvuHs8cVukohqqkRA5IGFfx3MqKq9Z/ddFluxXZ0CLYTocC8JEcwJANarB
    Vu2CR9yguPrZUFo44Fm76+V1zDzNh4rX8XTyHF6eqiovnD+UhkFPgIhu2NQpwaju
    5ke+9wH1YISGV6uA+wJBALsrh9zNW/brxAnQ3wWBZcSPDzAHMuVc238dqNhsN0JA
    wU0seIAZvVJlYk5IohTL7JHapithdwi7h7AZiRDWdvE=
                                """;

    TimeCodeGenerator codegen(userKey, PassID, timeInterval);

    std::string generatedCode = codegen.generateTimeCode();

    EXPECT_TRUE(generatedCode.empty());
}


