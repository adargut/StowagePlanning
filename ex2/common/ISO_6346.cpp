#include "ISO_6346.h"

#include <regex>
#include <sstream>

bool ISO_6346::isValidId(const std::string& id, bool check_bureau, bool check_category) {

    std::stringstream id_format_to_enforce;
    id_format_to_enforce << owner_code_format << (check_category ? category_identifier_strict_format : category_identifier_format) << serial_number_format << check_digit_format;

    if (!std::regex_match(id, std::regex(id_format_to_enforce.str())))
        return false;

    // if check_bureau == true: check if owner code is registered at the Bureau International des Conteneurs
    if (check_bureau && !isOwnerCodeRegistered(id.substr(begin_pos, owner_code_size)))
        return false;

    return CheckDigit::checkDigit(id);
}

bool ISO_6346::CheckDigit::checkDigit(const std::string& id) {
    int sum = 0;
    for (int i=0; i<check_digit_pos; ++i) {
        sum += pow(check_digit_multiplier_base,i) * CharCoder::code(id[i]);
    }

    int check_digit = sum - std::floor(sum / devision_value) * devision_value;
    return (check_digit % numeric_base) == CharCoder::code(id[check_digit_pos]);
}
