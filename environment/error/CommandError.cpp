#include "CommandError.hpp"

namespace hlt {

/**
 * Convert a direction to a string.
 * @param direction The direction.
 * @return The direction as a string.
 */
std::string direction_to_string(Direction direction) {
    std::string result;
    switch (direction) {
    case Direction::North:
        result = "north";
        break;
    case Direction::South:
        result = "south";
        break;
    case Direction::East:
        result = "east";
        break;
    case Direction::West:
        result = "west";
        break;
    }
    return result;
}

/**
 * Get a message for the player log.
 * @return The message.
 */
std::string ExcessiveCommandsError::log_message() const {
    std::ostringstream stream;
    stream << "entity "
           << entity
           << " received "
           << context().size()
           << " commands on this turn, but only one is permitted.";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
std::string ExcessiveSpawnsError::log_message() const {
    return "received more than one spawn command on this turn.";
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string EntityNotFoundError<DumpCommand>::log_message() const {
    std::ostringstream stream;
    stream << "unknown entity "
           << command().entity
           << " was requested to dump "
           << command().energy
           << ".";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string EntityNotFoundError<ConstructCommand>::log_message() const {
    std::ostringstream stream;
    stream << "unknown entity "
           << command().entity
           << " was requested to construct.";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string EntityNotFoundError<MoveCommand>::log_message() const {
    std::ostringstream stream;
    stream << "unknown entity "
           << command().entity
           << " was requested to move "
           << direction_to_string(command().direction)
           << ".";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string InsufficientEnergyError<MoveCommand>::log_message() const {
    std::ostringstream stream;
    stream << "entity "
           << command().entity
           << " was directed to use "
           << requested
           << " energy to move "
           << direction_to_string(command().direction)
           << ", but only "
           << available
           << " energy was available.";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string InsufficientEnergyError<DumpCommand>::log_message() const {
    std::ostringstream stream;
    stream << "entity "
           << command().entity
           << " was directed to dump "
           << requested
           << " energy, but only "
           << available
           << " energy was available.";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
std::string PlayerInsufficientEnergyError::log_message() const {
    std::ostringstream stream;
    stream << "player attempted to use "
           << requested
           << " energy, but only "
           << available
           << " was available.";
    return stream.str();
}

/**
 * Get a message for the player log.
 * @return The message.
 */
template<>
std::string CellOwnedError<ConstructCommand>::log_message() const {
    std::ostringstream stream;
    stream << "entity "
           << command().entity
           << " was directed to construct at ("
           << cell.x
           << ", "
           << cell.y
           << "), but that cell was already owned by player "
           << player
           << ".";
    return stream.str();
}

}
