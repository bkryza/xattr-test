# XAttr test

This is a very basic program testing support and validity of xattr support
in the underlying filesystem.

## Building

```
cmake .
make
```

## Example usage

### Prepare test file:
```
$ cd <DIRECTORY_ON_TARGET_FILESYSTEM>
$ touch test_file.txt

# On Linux xattr tool has to installed manually
$ sudo apt-get install python-xattr
```

### Run test
```
$ ./xattr-test test_file.txt

Setting attribute string value should work...OK
Setting attribute with empty value should work...OK
Setting attribute with Json string should be properly escaped...OK
Setting attribute with Json string should be properly escaped...OK
Setting attribute with Json number value should work...OK
Setting attribute with Json boolean value should work...OK
Setting attribute with new line characters should work...OK
Setting attribute with unicode characters should work...OK
Setting attribute with long unicode text should work...OK
Setting attribute with any characters should work...OK
Setting attribute with binary value should work...OK
Setting attribute with long binary value should work...OK
Setting string attribute with empty name should not work...OK
Setting attribute string value should work...OK
Existing attribute should not be replaced with XATTR_CREATE...OK
Non existing attributed should not be replaced with XATTR_REPLACE...OK
```

### List the extended attribute names
```
$ xattr test_file.txt

TO_BE_REPLACED
binaryAttribute
emptyAttribute
gifImage
jsonBooleanAttribute
jsonInvalidObjectString
jsonLongUnicodeAttribute
jsonMultilineAttribute
jsonNumberAttribute
jsonString
jsonStringSymbols
jsonUnicodeAttribute
stringAttribute
```

### Get all extended attribute names and values
```
$ xattr -l test_file.txt

TO_BE_REPLACED: VALUE
binaryAttribute:
00000000  41 00 42 00 43                                   |A.B.C|
00000005
emptyAttribute:
gifImage:
00000000  47 49 46 38 39 61 3D 00 44 00 F7 A8 00 9A 2C 33  |GIF89a=.D.....,3|
00000010  FF C0 C0 EF C0 C0 75 58 67 FC F9 F7 99 33 00 FF  |......uXg....3..|
00000020  EC EC FF A0 A0 E5 CC BF CF 9F 87 0F EF EF 7F 7F  |................|
00000030  7F EF 0F 0F DF 1F 1F FF 26 26 5F 9F 9F FF 59 59  |........&&_...YY|
00000040  BF 3F 3F 35 A5 C2 FF FF FF AC 16 19 B2 26 00 F8  |.??5.........&..|
00000050  13 10 C2 26 20 DF 60 50 50 84 9B F8 03 00 B5 0B  |...& .`PP.......|
00000060  0C DF 0F 00 3E 9A B5 87 42 4D 7F 60 50 D2 A5 8F  |....>...BM.`P...|
00000070  CC 19 00 A5 2C 00 EC D9 CF E5 0C 00 EB 09 00 FF  |....,...........|
00000080  D9 D9 C7 0C 0C 0F 0F 0F FF 79 79 7E 4D 5A FB 09  |.........yy~MZ..|
00000090  08 E5 4D 40 FB 5F 5F FF 33 33 CF 90 78 F2 E5 DF  |..M@.__.33..x...|
000000A0  C3 06 06 BF 09 08 FF B3 B3 D9 B2 9F FF 06 06 AC  |................|
000000B0  29 00 FF C6 C6 0C 09 08 F9 F2 EF C9 73 60 B8 23  |)...........s`.#|

...

jsonMultilineAttribute:
LINE1
LINE2
LINE3
jsonNumberAttribute: -123.89
jsonString: asdasd"adsdas'asdda
jsonStringSymbols: !@#O!@O#Y!OI@U!@*!*@"<,...,\t\n\\00\0\0\0?><>:|"|||{:}_!(@)(#*!@*#&!(@#*&£§§§))))``````
jsonUnicodeAttribute: महसुस
stringAttribute: stringValue
```

### Get specific extended attribute value
```
$ xattr -p jsonLongUnicodeAttribute test_file.txt

चिदंश मुश्किले अर्थपुर्ण पसंद स्थिति आशाआपस सोफ़्टवेर बलवान मानव बनाने वास्तव कार्यसिधान्तो आपके उसके तरहथा। प्राथमिक मजबुत बनाकर करते निर्माण आंतरजाल भाषा बढाता गटकउसि निर्देश विचारशिलता रखति शारिरिक व्रुद्धि प्रोत्साहित करता। उन्हे एकत्रित जानकारी सुस्पश्ट कारन उनका सभीकुछ निरपेक्ष लाभान्वित डाले। संपादक विकेन्द्रियकरण समूह बनाना ध्येय मुखय दिशामे बातसमय व्याख्या
नवंबर अपने संस्था आवश्यक उपलब्ध करता आशाआपस दिनांक बनाने सकती बाजार खयालात ऎसाजीस उनका सुचना गुजरना पुस्तक मुश्किले आजपर ध्येय पुस्तक किएलोग आंतरकार्यक्षमता
आशाआपस असरकारक कर्य करता। जोवे पहेला उपेक्ष समस्याए भेदनक्षमता अतित समजते संस्था प्रमान विकेन्द्रियकरण बढाता द्वारा यन्त्रालय चाहे तकनिकल दर्शाता हार्डवेर आपको सुचना जाता असरकारक अविरोधता लाभान्वित बाजार जिम्मे प्रदान व्यवहार समाजो अतित एसेएवं सोफ़्टवेर अंग्रेजी सीमित गएआप एकएस आवश्यक उसीएक् निरपेक्ष हिंदी
उपलब्ध नयेलिए सामूहिक सादगि सुनत नीचे बनाना ब्रौशर दिनांक पुष्टिकर्ता भारतीय किएलोग केन्द्रित साधन बाटते सभिसमज बिन्दुओ मार्गदर्शन विकास जाएन वर्णन अपने है।अभी प्राप्त स्थापित विकेन्द्रित सुचनाचलचित्र ढांचामात्रुभाषा करती प्राण विभाग मानव असक्षम वैश्विक उपलब्धता और्४५० कार्यसिधान्तो चुनने जाने प्रति प्रमान वर्तमान समस्याए सकता गुजरना निर्देश विश्लेषण बिना होसके देखने स्थिति सोफ़तवेर सकती
ध्वनि रखति पासपाई असक्षम समस्याए बलवान २४भि हमेहो। अमितकुमार भारत संदेश असक्षम निर्देश विकेन्द्रित ऎसाजीस प्रेरना बढाता बिना जिसकी कार्यकर्ता प्रतिबध्दता जैसी विषय बलवान क्षमता अविरोधता हार्डवेर मजबुत संपादक प्रतिबध २४भि भाषए जिम्मे क्षमता। बनाना बनाति कलइस उपलब्ध तकरीबन सुस्पश्ट गएआप अनुवाद वार्तालाप बाटते पहोचने वेबजाल विश्लेषण लगती प्रति क्षमता वर्तमान सुचनाचलचित्र बाधा समाजो मानसिक व्याख्या व्याख्यान सादगि जोवे लचकनहि निर्माता हैं। प्रति
जिवन हमारी संपुर्ण विश्वव्यापि जाने नवंबर खयालात व्याख्यान ढांचा समाज पहोचने अनुवादक शुरुआत पहोचने सामूहिक जाएन संदेश किया भोगोलिक मुश्किले विकासक्षमता औषधिक उन्हे मेमत दोषसके गयेगया प्रौध्योगिकी डाले। असक्षम वातावरण संस्थान लगती जिवन स्थिति परिवहन पासपाई डाले।

...
```
