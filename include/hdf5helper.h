#include "H5Cpp.h"

namespace hdf5helper {
    template <typename T>
    bool groupExists(T group, std::string name)
    {
        try {
            group.openGroup(name);
            return true;
        }
        catch(H5::GroupIException) {
            return false;
        }
    }
}
