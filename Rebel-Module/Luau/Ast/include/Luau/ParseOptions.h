// This file is part of the Luau programming language and is licensed under MIT License; see LICENSE.txt for details
#pragma once

#include "Ast.h"
#include "../../../Common/include/Luau/DenseHash.h"

#include <vector>

namespace Luau
{

enum class Mode
{
    NoCheck,    // Do not perform any inference
    Nonstrict,  // Unannotated symbols are any
    Strict,     // Unannotated symbols are inferred
    Definition, // Type definition module, has special parsing rules
};

struct FragmentParseResumeSettings
{
    DenseHashMap<AstName, AstLocal*> localMap{AstName()};
    std::vector<AstLocal*> localStack;
};

struct ParseOptions
{
    bool allowDeclarationSyntax = false;
    bool captureComments = false;
    std::optional<FragmentParseResumeSettings> parseFragment = std::nullopt;
};

} // namespace Luau