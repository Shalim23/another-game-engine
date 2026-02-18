module age_engine;

namespace age
{
    SystemManager::~SystemManager()
    {
        // Destroy in reverse order of registration
        for (std::size_t i{mEntries.size()}; i > 0; --i)
        {
            auto& entry{mEntries[i - 1]};
            entry.destroy(mBuffer.data() + entry.offset);
        }
    }


    void SystemManager::UpdateAll(float dt)
    {
        for (std::size_t i{0}; i < mEntries.size(); ++i)
        {
            auto& entry{mEntries[i]};
            entry.update(mBuffer.data() + entry.offset, dt);
        }
    }
}
