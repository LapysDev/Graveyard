/* Import */
#include <cstdio> // C Standard Input/ Output
#include <cstdlib> // C Standard Library
#include <cstring> // C String
#include <cwchar> // C Wide Characters
#include <iostream> // Input/ Output
#include <string> // String
#include <sstream> // String Stream

/* Definition > ... */
template <typename> struct class_t;
template <typename> struct MeGaSTRuCT;

#undef UNICODE

/* Definition > Class Type (Of) */
template <typename classType> struct class_t final { typedef classType type; };
template <> struct class_t<char> final { typedef class_t<void> type; };
template <> struct class_t<char const> final { typedef class_t<void> type; };
template <> struct class_t<double> final { typedef class_t<void> type; };
template <> struct class_t<double const> final { typedef class_t<void> type; };
template <> struct class_t<float> final { typedef class_t<void> type; };
template <> struct class_t<float const> final { typedef class_t<void> type; };
template <> struct class_t<long double> final { typedef class_t<void> type; };
template <> struct class_t<long double const> final { typedef class_t<void> type; };
template <> struct class_t<signed char> final { typedef class_t<void> type; };
template <> struct class_t<signed char const> final { typedef class_t<void> type; };
template <> struct class_t<signed int> final { typedef class_t<void> type; };
template <> struct class_t<signed int const> final { typedef class_t<void> type; };
template <> struct class_t<signed long int> final { typedef class_t<void> type; };
template <> struct class_t<signed long int const> final { typedef class_t<void> type; };
template <> struct class_t<signed short int> final { typedef class_t<void> type; };
template <> struct class_t<signed short int const> final { typedef class_t<void> type; };
template <> struct class_t<unsigned char> final { typedef class_t<void> type; };
template <> struct class_t<unsigned char const> final { typedef class_t<void> type; };
template <> struct class_t<unsigned int> final { typedef class_t<void> type; };
template <> struct class_t<unsigned int const> final { typedef class_t<void> type; };
template <> struct class_t<unsigned long int> final { typedef class_t<void> type; };
template <> struct class_t<unsigned long int const> final { typedef class_t<void> type; };
template <> struct class_t<unsigned short int> final { typedef class_t<void> type; };
template <> struct class_t<unsigned short int const> final { typedef class_t<void> type; };
template <> struct class_t<wchar_t> final { typedef class_t<void> type; };
template <> struct class_t<wchar_t const> final { typedef class_t<void> type; };
template <> struct class_t<void> final { typedef class_t<void> type; };
template <> struct class_t<void const> final { typedef class_t<void> type; };
template <typename plainType> struct class_t<plainType*> final { typedef class_t<void> type; };
template <typename plainType> struct class_t<plainType* const> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const volatile> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const volatile&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)const volatile&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)volatile> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)volatile&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes...)volatile&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const volatile> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const volatile&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)const volatile&&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)volatile> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)volatile&> final { typedef class_t<void> type; };
template <typename plainType, typename... plainTypes> struct class_t<plainType (plainTypes..., ...)volatile&&> final { typedef class_t<void> type; };
template <typename plainType, std::size_t plainLength> struct class_t<plainType (&)[plainLength]> final { typedef class_t<void> type; };
template <typename plainType, std::size_t plainLength> struct class_t<plainType (*)[plainLength]> final { typedef class_t<void> type; };

#ifdef __cplusplus
#   if __cplusplus >= 201103L
        template <> struct class_t<char16_t> final { typedef class_t<void> type; };
        template <> struct class_t<char32_t> final { typedef class_t<void> type; };
        template <> struct class_t<signed long long int> final { typedef class_t<void> type; };
        template <> struct class_t<unsigned long long int> final { typedef class_t<void> type; };
#   endif

#   if __cplusplus > 201703L
        template <> struct class_t<char8_t> final { typedef class_t<void> type; };
#   endif
#endif

template <typename type>
struct MeGaSTRuCT final {
    /* Definition > ... */
    friend class class_t<type>::type;
    #if defined(__cplusplus) && __cplusplus < 201103L
        typedef unsigned long int length_t;
    #else
        typedef unsigned long long int length_t;
    #endif

    // [...]
    private:
        // Definitions > Items ...
        void *items;
        length_t itemsLength;
        length_t itemsOffset;

        // Definition > Shove ...
        constexpr inline void shove(length_t const, type* const, void (MeGaSTRuCT<type>::* const)(type* const, type* const))& noexcept;
        constexpr inline void shoveByInterface(type* const, type* const)& noexcept;
        constexpr inline void shoveByReference(type* const, type* const) /* const */ volatile& noexcept;

    // [...]
    public:
        // [Constructor, Destructor]
        constexpr inline MeGaSTRuCT<type>(...);
        inline ~MeGaSTRuCT<type>(void);

        // Definition
            // Blammo
            template <typename... types> constexpr inline void blammo(length_t const, length_t const, types...)& noexcept;
            template <typename... types> constexpr inline static void blammo(MeGaSTRuCT<type>&, length_t const, length_t const, types...) noexcept;

            // Shove
            constexpr inline void shove(length_t const, type&) const volatile& noexcept;
            constexpr inline void shove(length_t const, type&&) const& noexcept;
            constexpr inline static void shove(MeGaSTRuCT<type>&, length_t const, type&) noexcept;
            constexpr inline static void shove(MeGaSTRuCT<type>&, length_t const, type&&) noexcept;

            // Stringify
            #ifdef UNICODE
                inline wchar_t* stringify(length_t const) const volatile& noexcept;
                inline static wchar_t* stringify(MeGaSTRuCT<type>&, length_t const) noexcept;
            #else
                inline char* stringify(length_t const) const volatile& noexcept;
                inline static char* stringify(MeGaSTRuCT<type>&, length_t const) noexcept;
            #endif

            // Yoink
            constexpr inline type& yoink(length_t const) const volatile& noexcept;
            constexpr inline static type& yoink(MeGaSTRuCT<type>&, length_t const) noexcept;
};

/* Modification > ... */
    // [👶 Constructor, 👴 Destructor]
    template <typename type> constexpr inline MeGaSTRuCT<type>::MeGaSTRuCT(...) try : items{nullptr}, itemsLength{0uL}, itemsOffset{0uL} {} catch (...) { throw; } {}
    template <typename type> inline MeGaSTRuCT<type>::~MeGaSTRuCT<type>(void) { delete[] static_cast<type*>(this -> ::MeGaSTRuCT<type>::items); }

    // 💣 Blammo
    template <typename type> template <typename... types>
    constexpr inline void MeGaSTRuCT<type>::blammo(length_t const length, length_t const offset, types... arguments)& noexcept {
        delete[] (this -> ::MeGaSTRuCT<type>::items);

        this -> ::MeGaSTRuCT<type>::items = static_cast<void*>(new type[length] {arguments...});
        this -> ::MeGaSTRuCT<type>::itemsLength = length;
        this -> ::MeGaSTRuCT<type>::itemsOffset = offset;
    }

    template <typename type> template <typename... types>
    constexpr inline void MeGaSTRuCT<type>::blammo(MeGaSTRuCT<type>& structure, length_t const length, length_t const offset, types... arguments) noexcept { return structure.::MeGaSTRuCT<type>::blammo(length, offset, arguments...); }

    // ⛏️ Shove ...
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shove(length_t const index, type& item) const volatile& noexcept { this -> ::MeGaSTRuCT<type>::shove(index, &item, &(this -> ::MeGaSTRuCT<type>::shoveByReference)); }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shove(length_t const index, type&& item) const& noexcept { this -> ::MeGaSTRuCT<type>::shove(index, &item, &(this -> ::MeGaSTRuCT<type>::shoveByInterface)); }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shove(MeGaSTRuCT<type>& structure, length_t const index, type& item) noexcept { return structure.::MeGaSTRuCT<type>::shove(index, item); }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shove(MeGaSTRuCT<type>& structure, length_t const index, type&& item) noexcept { return structure.::MeGaSTRuCT<type>::shove(index, item); }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shove(length_t const index, type* const item, void (MeGaSTRuCT<type>::* const shover)(type* const, type* const))& noexcept { (this ->* ::MeGaSTRuCT<type>::shover)(static_cast<type*&>(this -> ::MeGaSTRuCT<type>::items) + ((this -> ::MeGaSTRuCT<type>::itemsOffset + index + 3uL) % this -> ::MeGaSTRuCT<type>::itemsLength), item); }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shoveByInterface(type* const index, type* const item)& noexcept { *index = *item; }
    template <typename type> constexpr inline void MeGaSTRuCT<type>::shoveByReference(type* const index, type* const item) /* const */ volatile& noexcept { std::memcpy(index, item, sizeof(type)); }

    // 🕸️ Stringify
    #ifdef UNICODE
        template <typename type>
        inline wchar_t* MeGaSTRuCT<type>::stringify(length_t const index) const volatile& noexcept {
            static wchar_t message[256] = {0};
            std::wstringstream stream = {};

            stream.std::wstringstream::operator <<(this -> ::MeGaSTRuCT<type>::yoink(index));

            std::wcsncpy(message, L"The value is ", 13u);
            std::wcscpy(message, stream.str().c_str());

            std::wcout.write(message, std::wcslen(message));

            return message;
        }
        template <typename type> inline wchar_t* MeGaSTRuCT<type>::stringify(MeGaSTRuCT<type>& structure, length_t const index) noexcept { return structure.::MeGaSTRuCT<type>::stringify(index); }
    #else
        template <typename type>
        inline char* MeGaSTRuCT<type>::stringify(length_t const index) const volatile& noexcept {
            static char message[256] = {0};
            std::stringstream stream = {};

            stream.std::stringstream::operator <<(this -> ::MeGaSTRuCT<type>::yoink(index));

            std::strncpy(message, "The value is ", 13u);
            std::strcpy(message, stream.str().c_str());

            std::cout.write(message, std::strlen(message));

            return message;
        }
        template <typename type> inline char* MeGaSTRuCT<type>::stringify(MeGaSTRuCT<type>& structure, length_t const index) noexcept { return structure.::MeGaSTRuCT<type>::stringify(index); }
    #endif

    // 🎣 Yoink
    template <typename type> constexpr inline type& MeGaSTRuCT<type>::yoink(length_t const index) const volatile& noexcept { return *(static_cast<type*>(this -> ::MeGaSTRuCT<type>::items) + ((this -> ::MeGaSTRuCT<type>::itemsOffset + index) % this -> ::MeGaSTRuCT<type>::itemsLength)); }
    template <typename type> constexpr inline type& MeGaSTRuCT<type>::yoink(MeGaSTRuCT<type>& structure, length_t const index) noexcept { return structure.::MeGaSTRuCT<type>::yoink(index); }

/* Main */
int main(int const, char const* const[]) {
    // Global > Exit Code
    int exitCode = EXIT_SUCCESS;

    // Constant > Structure
    MeGaSTRuCT<char const* const> const structure = {"Hello, World!"};
    (void) structure;

    // Terminate
    return exitCode;
}
