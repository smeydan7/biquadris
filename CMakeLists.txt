cmake_minimum_required(VERSION 3.25)
project(biquadris)

set(CMAKE_CXX_STANDARD 20)

add_executable(biquadris main.cc Board.h Block.h Position.cc Blocks/IBlock.cc Blocks/IBlock.h Board.cc Game.cc Game.h Blocks/JBlock.cc Blocks/JBlock.h Blocks/LBlock.cc Blocks/LBlock.h Blocks/OBlock.cc Blocks/OBlock.h Blocks/SBlock.cc Blocks/SBlock.h Blocks/ZBlock.cc Blocks/ZBlock.h Blocks/TBlock.cc Blocks/TBlock.h Position.h Block.cc Level.h Level.cc Levels/Level0.h Levels/Level0.cc Levels/Level1.cc Levels/Level1.h Levels/Level2.cc Levels/Level2.h Levels/Level3.cc Levels/Level3.h Levels/Level4.cc Levels/Level4.h trie-impl.cc score.h score.cc)
