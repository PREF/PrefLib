#ifndef PREFLIB_CORE_CONTAINERS_CACHEDMAP_H
#define PREFLIB_CORE_CONTAINERS_CACHEDMAP_H

#include <map>
#include <queue>
#include <cstdio>
#include <cstring>
#include <type_traits>

namespace PrefLib {
namespace Core {
namespace Containers {

template<typename V> struct cache
{
    void write(FILE * fp, const V& v) const { std::fwrite(&v, sizeof(V), 1, fp); }
    void read(FILE* fp, V* v) { std::fread(v, sizeof(V), 1, fp); }
};

template<typename K, typename V, typename W = cache<V>, typename C = std::less<K> > class CachedMap
{
    private:
        typedef CachedMap<K, V, W, C> CachedMapType;
        typedef std::queue<uint64_t> DeletedQueue;
        typedef std::map<K, uint64_t, C> MapType;

    public:
        typedef typename MapType::iterator iterator;
        typedef typename MapType::const_iterator const_iterator;

    private:
        class CachedItem
        {
            public:
                CachedItem(CachedMapType& owner, K& key): _owner(owner), _key(key) { }
                CachedMapType& operator =(V& v) { this->_owner.insert(this->_key, v); return this->_owner; }
                operator V() const { return this->_owner.get(this->_key); }

            private:
                CachedMapType& _owner;
                K& _key;
        };

    public:
        CachedMap();
        ~CachedMap();

    private:
        uint64_t seekOffset();
        uint64_t cacheValue(const V& v);

    public:
        void insert(K &key, const V& value);
        const V &get(K &key);
        size_t size() const;
        bool empty() const;

    public:
        CachedItem operator[](K& k);

    private:
        FILE* _fp;
        DeletedQueue _queue;
        MapType _map;
        W _cacheobj;
        V _data;
};

template<typename K, typename V, typename W, typename C> CachedMap<K, V, W, C>::CachedMap()
{
    this->_fp = std::tmpfile();
}

template<typename K, typename V, typename W, typename C> CachedMap<K, V, W, C>::~CachedMap()
{
    if(this->_fp)
    {
        std::fclose(this->_fp);
        this->_fp = nullptr;
    }
}

template<typename K, typename V, typename W, typename C> uint64_t CachedMap<K,V, W, C>::seekOffset()
{
    if(!this->_queue.empty()) /* Recycle deleted items, if any */
    {
        uint64_t offset = this->_queue.front();

        this->_queue.pop();
        return offset;
    }

    std::fseek(this->_fp, 0, SEEK_END); /* Append Data */
    return std::ftell(this->_fp);
}

template<typename K, typename V, typename W, typename C> uint64_t CachedMap<K,V, W, C>::cacheValue(const V &v)
{
    uint64_t offset = this->seekOffset();
    this->_cacheobj.write(this->_fp, v);
    return offset;
}

template<typename K, typename V, typename W, typename C> void CachedMap<K, V, W, C>::insert(K& key, const V& value)
{
    this->_map[key] = this->cacheValue(value);
}

template<typename K, typename V, typename W, typename C> const V& CachedMap<K, V, W, C>::get(K& key)
{
    uint64_t offset = this->_map[key];

    std::fseek(this->_fp, offset, SEEK_SET);
    this->_cacheobj.read(this->_fp, &this->_data);
    return this->_data;
}

template<typename K, typename V, typename W, typename C> size_t CachedMap<K, V, W, C>::size() const
{
    return this->_map.size();
}

template<typename K, typename V, typename W, typename C> bool CachedMap<K, V, W, C>::empty() const
{
    return this->_map.empty();
}

template<typename K, typename V, typename W, typename C> typename CachedMap<K,V, W, C>::CachedItem CachedMap<K, V, W, C>::operator[](K &key)
{
    return typename CachedMap<K,V, W, C>::CachedItem(*this, key);
}

} // namespace Containers
} // namespace Core
} // namespace PrefLib

#endif // PREFLIB_CORE_CONTAINERS_CACHEDMAP_H
