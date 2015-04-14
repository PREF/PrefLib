#include "categorycontext.h"

namespace PrefLib {
namespace Format {

const char* CategoryContext::GLOBAL_CATEGORY = "(All)";
const char* CategoryContext::UNCATEGORIZED_CATEGORY = "(No Category)";

CategoryContext::CategoryContext()
{

}

CategoryContext::~CategoryContext()
{

}

void CategoryContext::add(FormatDefinition *formatdefinition)
{
    const char* category = formatdefinition->category();

    if(this->_formats.empty())
    {
        this->_categories.push_back(CategoryContext::GLOBAL_CATEGORY);
        this->_formats[CategoryContext::GLOBAL_CATEGORY] = FormatList();
    }

    if(strlen(category) <= 0)
    {
        if(!this->hasCategory(CategoryContext::UNCATEGORIZED_CATEGORY))
        {
            this->_categories.push_back(CategoryContext::UNCATEGORIZED_CATEGORY);
            this->_formats[CategoryContext::UNCATEGORIZED_CATEGORY] = FormatList();
        }

        this->_formats[CategoryContext::GLOBAL_CATEGORY].push_back(formatdefinition);
        this->_formats[CategoryContext::UNCATEGORIZED_CATEGORY].push_back(formatdefinition);
        return;
    }

    if(!this->hasCategory(category))
    {
        this->_categories.push_back(category);
        this->_formats[category] = FormatList();
    }

    this->_formats[CategoryContext::GLOBAL_CATEGORY].push_back(formatdefinition);
    this->_formats[category].push_back(formatdefinition);
}

const CategoryContext::CategoryList &CategoryContext::categories() const
{
    return this->_categories;
}

const CategoryContext::FormatList &CategoryContext::global() const
{
    return this->formats(CategoryContext::GLOBAL_CATEGORY);
}

const CategoryContext::FormatList &CategoryContext::formats(const char *category) const
{
    return this->_formats.at(category);
}

bool CategoryContext::hasCategory(const char *category) const
{
    return this->_formats.find(category) != this->_formats.cend();
}

} // namespace Format
} // namespace PrefLib

