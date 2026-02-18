module age_engine:system_manager;

import :concepts;
import <vector>;

namespace age
{

class SystemManager
{
    struct TypeIdGenerator
    {
        static inline std::size_t sNextId{0};
        
        template<typename T>
        static std::size_t GetId()
        {
            static const std::size_t id{sNextId++};
            return id;
        }
    };

    struct SystemEntry
    {
        std::size_t offset{};
        std::size_t size{};
        void (*update)(void*, float){nullptr};
        void (*destroy)(void*){nullptr};
    };

    public:
        SystemManager() = default;
        ~SystemManager();

        SystemManager(const SystemManager&) = delete;
        SystemManager& operator=(const SystemManager&) = delete;
        SystemManager(SystemManager&&) noexcept = delete;
        SystemManager& operator=(SystemManager&&) noexcept = delete;


        //# TODO rework to register systems as batch and check for unique types at compile time
        // accept a variadic list of system types and their constructor arguments
        // combine with an engine systems list to ensure all required systems are registered and no duplicates exist
        // reserve buffer space for all systems at once to avoid fragmentation and improve cache locality
        template<System T, typename... Args>
        T& AddSystem(Args&&... args)
        {
            const auto typeId{TypeIdGenerator::GetId<T>()};

            if (typeId < mTypeIndex.size() && mTypeIndex[typeId] != InvalidIndex)
            {
                return *reinterpret_cast<T*>(mBuffer.data() + mEntries[mTypeIndex[typeId]].offset);
            }

            constexpr std::size_t alignment{alignof(T)};
            constexpr std::size_t size{sizeof(T)};

            // Align the current end of the buffer
            const std::size_t offset{Align(mBuffer.size(), alignment)};
            mBuffer.resize(offset + size);

            // Placement-new the system into the buffer
            T* ptr{new (mBuffer.data() + offset) T(std::forward<Args>(args)...)};

            // Store metadata
            const std::size_t entryIndex{mEntries.size()};
            mEntries.push_back({
                .offset = offset,
                .size = size,
                .update = [](void* instance, float dt) { static_cast<T*>(instance)->Update(dt); },
                .destroy = [](void* instance) { static_cast<T*>(instance)->~T(); }
            });

            if (typeId >= mTypeIndex.size())
            {
                mTypeIndex.resize(typeId + 1, InvalidIndex);
            }
            mTypeIndex[typeId] = entryIndex;

            return *ptr;
        }

        template<typename T>
        T& GetSystem()
        {
            const auto typeId{TypeIdGenerator::GetId<T>()};
            return *reinterpret_cast<T*>(mBuffer.data() + mEntries[mTypeIndex[typeId]].offset);
        }

        template<typename T>
        const T& GetSystem() const
        {
            const auto typeId{TypeIdGenerator::GetId<T>()};
            return *reinterpret_cast<const T*>(mBuffer.data() + mEntries[mTypeIndex[typeId]].offset);
        }

        template<typename T>
        bool HasSystem() const
        {
            const auto typeId{TypeIdGenerator::GetId<T>()};
            return typeId < mTypeIndex.size() && mTypeIndex[typeId] != InvalidIndex;
        }

        void UpdateAll(float dt);

    private:
        std::size_t Align(std::size_t offset, std::size_t alignment)
        {
            return (offset + alignment - 1) & ~(alignment - 1);
        }

    private:
        std::vector<std::byte> mBuffer;
        std::vector<SystemEntry> mEntries;
        std::vector<std::size_t> mTypeIndex;
        static constexpr std::size_t InvalidIndex{static_cast<std::size_t>(-1)};
};

} // namespace age