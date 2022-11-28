cmake_minimum_required(VERSION 3.23)

# Define project
project(
        Beans
        VERSION 1.0
        LANGUAGES CXX
)

# Set CMAKE variables
set(CMAKE_CXX_STANDARD 14)

add_executable(Beans main.cpp Cards/Card.h Cards/Blue.h Cards/Chili.h Cards/Stink.h Cards/Green.h Cards/Soy.h Cards/Black.h Cards/Red.h Cards/Garden.h Structures/Chain.h Structures/Deck.h CardFactory.h Structures/DiscardPile.h Player.h Exceptions/NotEnoughCoinsException.h Structures/Hand.h Structures/Table.h Structures/TradeArea.h Constants.h CardFactory.cpp Exceptions/DeckEmptyException.h Exceptions/IllegalTypeException.h Structures/ChainBase.h)