#ifndef DATAHANDLER_H
#define DATAHANDLER_H
#include "H5Cpp.h"
#include <boost/filesystem.hpp>
#include "logger.h"

namespace fs = boost::filesystem;

namespace DataHandling {
    enum file_state{
        READ,
        WRITE,
        RDWR,
        TRUNC
    };

    class GroupHandler {
        public:
            virtual ~GroupHandler() {};
    };
    
    class DataHandler {
        public:
            virtual ~DataHandler() {};
            virtual std::unique_ptr<GroupHandler> create_group(const std::string& name) = 0;
            virtual std::unique_ptr<GroupHandler> open_group(const std::string& name) = 0;
            virtual bool group_exists(const std::string& name) = 0;
        private:
    };

    class HDF5GroupHandler : public GroupHandler {
        public:
            HDF5GroupHandler(H5::Group g) : data_group(g) {};
            ~HDF5GroupHandler() {};
        private:
            H5::Group data_group;
    };

    class HDF5Handler : public DataHandler {
        public:
            HDF5Handler(fs::path data_path, file_state state) {
                try {
                    switch(state) {
                        case READ:
                            data_file = H5::H5File(data_path.string(), H5F_ACC_RDONLY);
                            break;
                        case RDWR:
                            data_file = H5::H5File(data_path.string(), H5F_ACC_RDONLY);
                            break;
                        case TRUNC:
                            data_file = H5::H5File(data_path.string(), H5F_ACC_TRUNC);
                            break;
                        case WRITE:
                            break;
                    }
                }
                catch(H5::FileIException) {
                    throw std::runtime_error("Error opening " + data_path.string());
                }
            }

            std::unique_ptr<GroupHandler> create_group(const std::string& name) {
                return std::make_unique<HDF5GroupHandler>(HDF5GroupHandler(data_file.createGroup(name)));
            }

            std::unique_ptr<GroupHandler> open_group(const std::string& name) {
                return std::make_unique<HDF5GroupHandler>(HDF5GroupHandler(data_file.openGroup(name)));
            }

            bool group_exists(const std::string& name)
            {
                try {
                    data_file.openGroup(name);
                    return true;
                }
                catch(H5::GroupIException) {
                    return false;
                }
            }
            ~HDF5Handler() {};
        private:
            H5::H5File data_file;
    };

    class NativeFSGroupHandler : public GroupHandler {
        public:
        private:
    };

    class NativeFSHandler : public DataHandler {
        public:
        private:
    };

    template <typename T>
    std::unique_ptr<DataHandler> create_handler(fs::path path, file_state state)
    {
        return std::make_unique<T>(T(path, state));
    }

}
#endif
