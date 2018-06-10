" Quit when a syntax file was already loaded.
if exists('b:current_syntax') | finish |  endif

syntax match GenName      /\i\+/ contained
syntax match GenExe       /[^ \t]\+/ contained
syntax match GenNameGV    /\i\+/ contained nextgroup=GenExe skipwhite
syntax match GenScore     /\d\+/ contained nextgroup=GenName skipwhite
syntax match GenNumber    /\d\+/ contained
syntax match GenVariable  /\$\i\+/
syntax match GenDollar    /\$\$/
syntax keyword GenGeneratorK contained GEN VAL nextgroup=GenNameGV skipwhite
syntax keyword GenRunK contained RUN nextgroup=GenName skipwhite
syntax keyword GenSubtaskK contained SUBTASK nextgroup=GenScore skipwhite
syntax keyword GenConstraintK contained CONSTRAINT nextgroup=GenNumber
syntax match GenCommand   /^:.*/ contains=GenGeneratorK,GenSubtaskK,GenRunK,GenVariable
syntax match GenConstraintCommand   /^:\s*CONSTRAINT.*/ contains=GenConstraintK,GenNumber,GenVariable
syntax match GenComment   /^#.*/

hi def link GenComment Comment
hi def link GenScore Number
hi def link GenNumber Number
hi def link GenName Identifier
hi def link GenNameGV Identifier
hi def link GenCommand Statement
hi def link GenConstraintCommand Statement
hi def link GenExe Special
hi def link GenGeneratorK vimCommand
hi def link GenRunK vimCommand
hi def link GenSubtaskK vimCommand
hi def link GenConstraintK vimCommand
hi def link GenVariable Macro
hi def link GenDollar Macro

let b:current_syntax = 'gen'
