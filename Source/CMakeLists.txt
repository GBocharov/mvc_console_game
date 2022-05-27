cmake_minimum_required(VERSION 3.17)
project(Game)

set(CMAKE_CXX_STANDARD 14)

add_executable(Game
        Main.cpp
        Player/Player.cpp Player/Player.h
        Log/Logger.h
        Stream/Stream.h
        Stream/FileStream.cpp Stream/FileStream.h
        Stream/ConsoleStream.cpp Stream/ConsoleStream.h
        Log/ILogger.h
        Log/Logger.cpp
        Log/Loggable.h
        Log/LoggableInt32.cpp Log/LoggableInt32.h
        Log/Loggable.cpp
        Stream/MultipleStream.cpp Stream/MultipleStream.h
        Def.h
        Cell/Cell.h
        Cell/PassableCell.cpp Cell/PassableCell.h
        Cell/ImpassableCell.cpp Cell/ImpassableCell.h
        Cell/OrdinaryCell.cpp Cell/OrdinaryCell.h
        Buff/Buff.h
        Buff/Buff.cpp
        Map/Map.cpp Map/Map.h
        Log/LoggableCoord.cpp Log/LoggableCoord.h
        Game/Game.cpp Game/Game.h
        Input/Input.cpp Input/Input.h
        Enemy/Enemy.h Enemy/Enemy.cpp
        Cell/Cell.cpp
        Render/Framebuffer.cpp Render/Framebuffer.h Saveable/Saveable.h Log/ILoggable.cpp Log/ILoggable.h)
