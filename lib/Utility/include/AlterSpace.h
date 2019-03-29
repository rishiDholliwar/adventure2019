#ifndef ALTERSPACE_TYPES_H
#define ALTERSPACE_TYPES_H

#include <string>

namespace AlterSpace
{

	// 	// NOTE: This provides a strongly typed wrapper to prevent argument confusion.
	// // There are existing libraries and headers that can provide richer strongly
	// // typed aliases.
	// template <typename Base, typename Tag>
	// struct StrongAlias {
	//   explicit StrongAlias(Base value) : value{std::move(value)} { }
	//   Base value;
	// };

	// using RoomID = StrongAlias<int, struct RoomIDTag> != StrongAlias<int, struct ObjectIDTag>;
	// using ObjectID = StrongAlias<int, struct ObjectIDTag>;


    using Alias     = std::string;
    using ID        = unsigned int;
    using Input     = std::string;
    using Name      = std::string;
    using Password  = std::string;
    using Property  = std::string;
    using Value     = std::string;
    using Invocation= std::string;
}


#endif //ALTERSPACE_TYPES_H
