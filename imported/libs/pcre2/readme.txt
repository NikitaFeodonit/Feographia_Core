
Preparing pcre2 library with CrystaX NDK in Msys2 on Windows for Android
(this is similar on the other systems)


1. Get sources
Download from: http://pcre.org/

tar xvjf pcre2-10.21.tar.bz2


2. See in pcre2-10.21/NON-AUTOTOOLS-BUILD part "GENERIC INSTRUCTIONS FOR THE PCRE2 C LIBRARY"


3. Copying to project

cp pcre2-10.21/src/<list> <Feographia_Android>/fcore/imported/libs/pcre2/src

<list>:

config.h.generic
pcre2.h.generic
pcre2_auto_possess.c
pcre2_chartables.c.dist
pcre2_compile.c
pcre2_config.c
pcre2_context.c
pcre2_dfa_match.c
pcre2_error.c
pcre2_find_bracket.c
pcre2_internal.h
pcre2_intmodedep.h
pcre2_jit_compile.c
pcre2_jit_match.c
pcre2_jit_misc.c
pcre2_maketables.c
pcre2_match.c
pcre2_match_data.c
pcre2_newline.c
pcre2_ord2utf.c
pcre2_pattern_info.c
pcre2_serialize.c
pcre2_string_utils.c
pcre2_study.c
pcre2_substitute.c
pcre2_substring.c
pcre2_tables.c
pcre2_ucd.c
pcre2_ucp.h
pcre2_valid_utf.c
pcre2_xclass.c


# must be like so:
# <Feographia_Android>/fcore/imported/libs/pcre2/src
#     config.h.generic
#     pcre2.h.generic
#     pcre2_auto_possess.c
#     pcre2_chartables.c.dist
#     pcre2_compile.c
#     pcre2_config.c
#     pcre2_context.c
#     pcre2_dfa_match.c
#     pcre2_error.c
#     pcre2_find_bracket.c
#     pcre2_internal.h
#     pcre2_intmodedep.h
#     pcre2_jit_compile.c
#     pcre2_jit_match.c
#     pcre2_jit_misc.c
#     pcre2_maketables.c
#     pcre2_match.c
#     pcre2_match_data.c
#     pcre2_newline.c
#     pcre2_ord2utf.c
#     pcre2_pattern_info.c
#     pcre2_serialize.c
#     pcre2_string_utils.c
#     pcre2_study.c
#     pcre2_substitute.c
#     pcre2_substring.c
#     pcre2_tables.c
#     pcre2_ucd.c
#     pcre2_ucp.h
#     pcre2_valid_utf.c
#     pcre2_xclass.c


cp src/pcre2.h.generic src/pcre2.h
cp src/pcre2_chartables.c.dist src/pcre2_chartables.c


4. Configure config.h

EITHER:

Copy config.h
cp src/config.h.generic src/config.h
and configure config.h by hand (see in pcre2/NON-AUTOTOOLS-BUILD part "GENERIC INSTRUCTIONS FOR THE PCRE2 C LIBRARY")

OR:

See readme_config_h.txt for make automatically configuring of config.h
