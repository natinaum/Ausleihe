Ort
| <Ort>
| | objN.json (LINK)
| | Personen
| | | Symlink to Folder

Person
| <Name>
| | meta.json
| | objN.json (LINK)

Objekte
| objN.json



meta.json:
{
    name: <name>
    bio: <kurzbeschreibung>
    Anwesend: <normale Anwesenheitszeiten>
    Objekte{
        "obj",
        "obj"
    }
    Ort{
        "ort",
        "ort",
        "ort"
    }
}

objN.json:
{
    Bezeichnung:
    Art:
    Author:
    SN/ISBN:
    Verliehen:
}

Server-API.c ----------------------\
                                    \
WEB.php ----------------------------->        edit.c
                                    /
CLI.sh ----------------------------/

"Simple functions:"
edit get <path> <bezeichner> //prints value from json file
 - return objekts/value -> Extra Funktion für objekte
edit set <path> <bezeichner> <value> //sets value of json file

edit add <path> <bezeichner> <type(vorlage)>  //typ: Objekt/Person
edit link <path> <path> //links json file from objekt/person/ort folder (path --simlink--> path)


"complex" functions:
edit addPerson <Name>
edit lnadd <path> <type> <person/ort> //links object to person or place

