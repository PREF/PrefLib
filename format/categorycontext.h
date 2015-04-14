#ifndef PREFLIB_FORMAT_CATEGORYCONTEXT_H
#define PREFLIB_FORMAT_CATEGORYCONTEXT_H

#include <vector>
#include <map>
#include "formatdefinition.h"

namespace PrefLib {
namespace Format {

class CategoryContext
{    
    private:
        struct CategoryComparator { bool operator()(const char* s1, const char* s2) const { return std::strcmp(s1, s2) < 0; } };

    public:
        typedef std::vector<const char*> CategoryList;
        typedef std::vector<FormatDefinition*> FormatList;

    private:
        typedef std::map<const char*, FormatList, CategoryComparator> CategoryMap;

    public:
        CategoryContext();
        ~CategoryContext();

    public:
        void add(FormatDefinition* formatdefinition);
        bool hasCategory(const char* category) const;
        const CategoryList& categories() const;
        const FormatList& global() const;
        const FormatList& formats(const char* category) const;

    public:
        static const char* GLOBAL_CATEGORY;
        static const char* UNCATEGORIZED_CATEGORY;

    private:
        CategoryList _categories;
        CategoryMap _formats;
};

} // namespace Format
} // namespace PrefLib

#endif // PREFLIB_FORMAT_CATEGORYCONTEXT_H
