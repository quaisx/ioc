
#include <memory>
#include <map>
#include <iostream>
#include <functional>

using namespace std;

namespace qua {
    namespace ioc {
        class Container {
            private:
                class vPlaceHolder {
                    public:
                        virtual void __nop__() { /* vtable for the holder class created */}
                };
                template<typename T>
                class PlaceHolder : public vPlaceHolder {
                    public:
                        std::shared_ptr<T> instance;
                };
                std::map<string, std::function<void*()>> creator_map;
                std::map<string, shared_ptr<vPlaceHolder>> instance_map;
            public:
                template<typename T>
                shared_ptr<T> getInstance() {
                    shared_ptr<T> rv = nullptr;
                    if (instance_map.find(typeid(T).name() != instance_map.end())) {
                        shared_ptr<vPlaceHolder> vholder = instance_map[typeid(T).name()]
                        PlaceHolder<T> *pholder = dynamic_cast<PlaceHolder<T>*>(vholder.get())
                        rv = pholder->instance;
                    } else if (creator_map.find(typeid(T).name()) != creator_map.end() {
                        rv = make_shared(static_cast<T*> (creator_map[typeid(T).name()]))
                    }
                    return rv;
                }

                template<typename T, typename... Ts>
                void registerClass() {
                    creator_map[typeid(T).name()] = [this] (void) -> T* {
                        return new T(this->getInstance<Ts>()...);
                    }
                }
        };
    }
}