# KSP- [  ]Ninja Virtual Machine

Praktikums Projekt für *Konzepte systemnaher Programmierung WS 19/20*.

# Debuger

## Ideen

## von der referenz implementierung

- [x] beim start
  - [x] datei name
  - [x] anzahl instructions
  - [x] anzahl vars
- [ ] nach jeder anweisung
  - [ ] nächste instruction anzeigen
  - [x] nächste debug commands anzeigen
- [x] untermenüs
  - [x] inspect
  - [x] breakpoint
- [x] promt
  - [x] normal "Debug:"
  - [x] in (untermenü)  "Debug [untermenü]:"
- [x] bei commands nur ersten buchtaben testen
- [x] commands
  - [x] inspect
    - [ ] stack
    - [ ] data
  - [x] list
    - [x] wie ausgabe in vorherigen aufgaben
  - [x] breakpoint
    - [ ] [num] (set at num)
    - [ ] - [ ]1 (clear breakpoint)
    - [x] ret (no change)
  - [ ] step
  - [ ] run
  - [x] quit

## erweiterungs ideen

- [x] Farben
- [x] promt "Debug$"
- [ ] vtl nicht immer mögliche commands ausgeben
- [ ] untermenü optionen direkt mit angeben
- [ ] step [anzahl]?
- [ ] mehrere breakpoints
- [x] einheitliches zurück (quit oder exit)
- [ ] help command
- [ ] list programm run (mit allen inst auch bei jmp) ?
- [ ] die wiederkehrende Debug: commands nachicht besser hervorheben (oder command ausgaben) vtl. mit "==="
- [ ] aktuelle locale vars anzeigen (ohne rest vom stack) ? (bzw alles über fp)
- [ ] auszug vom stack / daten ?
- [ ] wie mit Errors umgehen ? 
- [ ] vtl var angeben, die nach jedem step angezeigt wird