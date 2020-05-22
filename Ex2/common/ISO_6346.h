// ISO_6346
// 
// Id System Format 
//
#pragma once

#include <string>
#include <cmath>

// ISO_6346 Id System Format:
// https://en.wikipedia.org/wiki/ISO_6346 
//
// Use static bool ISO_6346::isValidId defined to validate if container Id matches the ISO_6346 Id System Format
//
struct ISO_6346 {
    // Checks if given id is valid
    // Parameters:
    //  check_bureau - if true check if owner code is registered at the Bureau International des Conteneurs 
    //  check_category - enforce strict/relaxed check for equipment category identifier:
    //                   true -  enforce strict category check: allow U | J | Z only
    //                   false - enforce relaxed category check: allow any uppercase letter
    // Returns: 
    //  true if id is ISO_6346 valid and false otherwise
    static bool isValidId(const std::string& id, bool check_bureau = false, bool check_category = true);

private:    
    // section_name: |OwnerCode|CategoryIdentifier|SerialNumber|CheckDigit| 
    // start_pos:    |0        |3                 |4           |10        |
    // format:       |[A-Z]{3} |  [UJZ] / [A-Z]   |  [0-9]{6}  |  [0-9]   |
    
    // Format to be enforced is defined below:
    // ---------------------------------------
    
    static constexpr int begin_pos = 0;
    
    // OwnerCode:

    static constexpr int owner_code_size = 3;
    static constexpr char owner_code_format[] = "[A-Z]{3}";

    // Check if owner code is registered at the Bureau International des Conteneurs
    //
    // A stub: no need to implement this function
    static bool isOwnerCodeRegistered(const std::string& owner_code) {
        return !owner_code.empty();
    }
    
    // CategoryIdentifier - Equipment category identifier:

    static constexpr int category_identifier_size = 1;
    static constexpr char category_identifier_format[] = "[A-Z]";
    static constexpr char category_identifier_strict_format[] = "[UJZ]";
    
    // SerialNumber:

    static constexpr int serial_number_size = 6;    
    static constexpr char serial_number_format[] = "[0-9]{6}";
    
    // CheckDigit:

    static constexpr int check_digit_pos = begin_pos + owner_code_size + category_identifier_size + serial_number_size;    
    static constexpr char check_digit_format[] = "[0-9]";
        
    struct CheckDigit { 
        // See checkDigit algorithm here: https://en.wikipedia.org/wiki/ISO_6346 
        static bool checkDigit(const std::string& id);
        
    private:
        // Codes 'A' to 'Z' based on ISO_6346: From 10, skiping 11*i for evey i:
        // -----------------------------------------------------------------------------------------------------------------------------------
        // | A  | B  | C  | D  | E  | F  | G  | H  | I  | J  | K  | L  | M  | N  | O  | P  | Q  | R  | S  | T  | U  | V  | W  | X  | Y  | Z  |
        // -----------------------------------------------------------------------------------------------------------------------------------
        // | 10 | 12 | 13 | 14 | 15 | 16 | 17 | 18 | 19 | 20 | 21 | 23 | 24 | 25 | 26 | 27 | 28 | 29 | 30 | 31 | 32 | 34 | 35 | 36 | 37 | 38 |
        // -----------------------------------------------------------------------------------------------------------------------------------
        struct CharCoder {
            // Assums 'A' <= ch <= 'Z' or '0' <= ch <= '9'
            // Note: any other input is undefined!
            inline static int code(char ch) { 
                if (ch <= '9') 
                    return ch - '0';
                    
                // Following implements the encoding table above - Hard coding the table is perfectly fine and provides better runtime efficiency!
                float character_pos = static_cast<float>(ch - 'A');
                return first_code + character_pos + std::ceil(character_pos/first_code); 
            }
        private:
            static constexpr int first_code = 10;
        }; 
        
        static constexpr int check_digit_multiplier_base = 2;
        static constexpr int devision_value = 11;
        static constexpr int numeric_base = 10;
    };
};
