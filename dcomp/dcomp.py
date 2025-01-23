#!/usr/bin/env python3

import re
import sys
import os


# ======== Classes ========
class FunctionWrapper:
    def __init__(self, func_tup):
        self.tag = func_tup[0]
        self.parseFuncStr(func_tup[1])


    def parseFuncStr(self, func_str):
        r = re.search(r"(.*?)\((.*?)\).*", func_str);
        func_pre_str = r.group(1).split(" ")
        func_arg_str = r.group(2).split(",") if r.group(2) else []

        self.func_type = " ".join(func_pre_str[0:-1])
        self.func_name = func_pre_str[-1]
        self.func_args = [a.strip() for a in func_arg_str]


    def genMarkdownEntry(self):
        entry = "#### " + self.func_name + "\n"
        entry += self.tag + "\n\n"
        entry += "> `" + self.func_type + " " + self.func_name

        if self.func_args:
            entry += "(...);`\n\n"
        else:
            entry += "();`\n\n"

        entry += "Function description\n\n"
        entry += "**Arguments**:\n\n"

        for a in self.func_args:
            entry += "-`" + a + "`:\n"

        return entry


class DocFile:
    def __init__(self, filename):
        self.path = "#### [Index](index.html) > Sub-Directory"
        self.lines = []
        self.func_wrap = []

        try:
            with open(filename, "r") as file:
                self.lines = file.readlines()
        except:
            raise FileNotFoundError("No file with that name.")

        func_str = []
        for i in range(len(self.lines)):
            if ":F:" in self.lines[i]:
                tag = self.grabTag(i)
                func = self.grabFunction(i+1)
                func_str.append((tag, func)) 

        for t in func_str:
            self.func_wrap.append(FunctionWrapper(t))


    def linkPath(self, link_file):
        for dir in ["", "docs/"]:
            try:
                with open(f"{dir}{link_file}", "r") as file:
                    path = file.readlines()[0]
            except:
                continue

        if path is None:
            raise FileNotFoundError("No file to link to")

        file_re = re.search(r"([^/]+)\.md", link_file)
        file_name = file_re.group(1) + ".html" if file_re else ""

        if not re.search(r"#### \[.*?\]\(index.html\) > .*", path):
            return 

        path_split = path.split(" ")
        path_front = " ".join(path_split[:-1]).strip()
        path_back = "[" + path_split[-1].strip() + "](" + file_name + ") > Sub-Directory"

        self.path = path_front + " " + path_back


    def grabTag(self, i):
        tag = ""
        tag_re = re.search(r"/\*(.*?)\*/", self.lines[i])

        if tag_re: 
            tag = tag_re.group(1)
            tag = re.sub(":F:", "", tag).strip()

        return tag

            
    def grabFunction(self, i):
        func_re = re.search(r".*?\(.*", self.lines[i])

        if not func_re:
            return ""

        func_str = self.lines[i].strip()

        while not re.search(r".*?\).*", self.lines[i]):
            i += 1
            func_str += " " + self.lines[i].strip()

        return func_str


    def genMarkdownTable(self):
        table_str = "###### Functions\n"
        for w in self.func_wrap:
            table_str += "- [**" + w.func_name + "**](#"
            table_str += w.func_name.lower().replace(" ", "_")
            table_str += "): " + w.tag + "\n"

        return table_str


    def genMarkdownEntries(self):
        entries_str = ""

        for w in self.func_wrap:
            entries_str += w.genMarkdownEntry() + "\n"

        return entries_str


    def genMarkdownPage(self):
        page_str = self.path + "\n\n"
        page_str += "## Sub-Directory\n\nShort Description.\n\n###### Description\n\n###### Usage\n\n"
        page_str += self.genMarkdownTable()
        page_str += "\n---\n\n"
        page_str += self.genMarkdownEntries()

        return page_str


# ======== Constants ========
DEFAULT = 0
ENTRY = 1
TABLE = 2

current_state = DEFAULT
input_files = []
link_file = ""


# ======== Parsing Arguments ========
args = sys.argv
i = 1

while i < len(args):
    if args[i] == "-e" or args[i] == "--entry":
        current_state = ENTRY

    elif args[i] == "-t" or args[i] == "--table":
        current_state = TABLE

    elif args[i] == "-l" or args[i] == "--link":
        link_file = args[i+1]
        i +=2 
        continue

    else:
        input_files.append(args[i])

    i += 1

if not input_files:
    raise Exception("No input file")


# ======== Handling Arguments ========
os.chdir(os.getcwd())
doc = DocFile(input_files[0])

if link_file:
    doc.linkPath(link_file)

if current_state == ENTRY:
    print(doc.genMarkdownEntries())
elif current_state == TABLE:
    print(doc.genMarkdownTable())
else:
    print(doc.genMarkdownPage())
