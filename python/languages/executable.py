#!/usr/bin/env python3

from task_maker.languages import Language, LanguageManager


class LanguagePython(Language):
    @property
    def name(self):
        return "Executable"

    @property
    def source_extensions(self):
        return [""]


def register():
    LanguageManager.register_language(LanguagePython())
