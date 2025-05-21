/* ==================================== JUCER_BINARY_RESOURCE ====================================

   This is an auto-generated file: Any edits you make may be overwritten!

*/

#include <cstring>

namespace BinaryData
{

//================== ARLogo.svg ==================
static const unsigned char temp_binary_data_0[] =
"<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n"
"<svg id=\"Capa_2\" data-name=\"Capa 2\" xmlns=\"http://www.w3.org/2000/svg\" viewBox=\"0 0 976 558\">\n"
"  <defs>\n"
"    <style>\n"
"      .cls-1 {\n"
"        fill: #884ffc;\n"
"      }\n"
"    </style>\n"
"  </defs>\n"
"  <g id=\"Capa_1-2\" data-name=\"Capa 1\">\n"
"    <g>\n"
"      <rect class=\"cls-1\" y=\"283\" width=\"80\" height=\"29\"/>\n"
"      <circle class=\"cls-1\" cx=\"40\" cy=\"283\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"40\" cy=\"312\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"112\" y=\"239\" width=\"80\" height=\"103\"/>\n"
"      <circle class=\"cls-1\" cx=\"152\" cy=\"239\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"152\" cy=\"342\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"224\" y=\"98\" width=\"80\" height=\"373\"/>\n"
"      <circle class=\"cls-1\" cx=\"264\" cy=\"471\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"264\" cy=\"98\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"335\" y=\"195\" width=\"80\" height=\"180\"/>\n"
"      <circle class=\"cls-1\" cx=\"375\" cy=\"195\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"375\" cy=\"375\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"447\" y=\"38\" width=\"80\" height=\"480\"/>\n"
"      <circle class=\"cls-1\" cx=\"487\" cy=\"40\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"487\" cy=\"518\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"559\" y=\"179\" width=\"80\" height=\"188\"/>\n"
"      <circle class=\"cls-1\" cx=\"599\" cy=\"367\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"599\" cy=\"181\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"672\" y=\"139\" width=\"80\" height=\"271\"/>\n"
"      <circle class=\"cls-1\" cx=\"712\" cy=\"139\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"712\" cy=\"410\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"783\" y=\"233\" width=\"80\" height=\"104\"/>\n"
"      <circle class=\"cls-1\" cx=\"823\" cy=\"233\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"823\" cy=\"337\" r=\"40\"/>\n"
"    </g>\n"
"    <g>\n"
"      <rect class=\"cls-1\" x=\"896\" y=\"276\" width=\"80\" height=\"29\"/>\n"
"      <circle class=\"cls-1\" cx=\"936\" cy=\"276\" r=\"40\"/>\n"
"      <circle class=\"cls-1\" cx=\"936\" cy=\"305\" r=\"40\"/>\n"
"    </g>\n"
"  </g>\n"
"</svg>";

const char* ARLogo_svg = (const char*) temp_binary_data_0;


const char* getNamedResource (const char* resourceNameUTF8, int& numBytes);
const char* getNamedResource (const char* resourceNameUTF8, int& numBytes)
{
    unsigned int hash = 0;

    if (resourceNameUTF8 != nullptr)
        while (*resourceNameUTF8 != 0)
            hash = 31 * hash + (unsigned int) *resourceNameUTF8++;

    switch (hash)
    {
        case 0x014a9121:  numBytes = 2014; return ARLogo_svg;
        default: break;
    }

    numBytes = 0;
    return nullptr;
}

const char* namedResourceList[] =
{
    "ARLogo_svg"
};

const char* originalFilenames[] =
{
    "ARLogo.svg"
};

const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8);
const char* getNamedResourceOriginalFilename (const char* resourceNameUTF8)
{
    for (unsigned int i = 0; i < (sizeof (namedResourceList) / sizeof (namedResourceList[0])); ++i)
        if (strcmp (namedResourceList[i], resourceNameUTF8) == 0)
            return originalFilenames[i];

    return nullptr;
}

}
