# KSP-Ninja Virtual Machine

Praktikums Projekt für *Konzepte systemnaher Programmierung WS 19/20*.

# Debuger

## Ideen

## von der referenz implementierung

- beim start
  - datei name
  - anzahl instructions
  - anzahl vars
- nach jeder anweisung
  - nächste instruction anzeigen
  - nächste debug commands anzeigen
- untermenüs
  - inspect
  - breakpoint
- promt
  - normal "Debug:"
  - in (untermenü)  "Debug [untermenü]:"
- bei commands nur ersten buchtaben testen
- commands
  - inspect
    - stack
    - data
  - list
    - wie ausgabe in vorherigen aufgaben
  - breakpoint
    - [num] (set at num)
    - -1 (clear breakpoint)
    - ret (no change)
  - step
  - run
  - quit

## erweiterungs ideen

- Farben
- untermenü optionen direkt mit angeben
- step [anzahl]?
- mehrere breakpoints
- einheitliches zurück (quit oder exit)
- help command
- list programm run (mit allen inst auch bei jmp) ?
- die wiederkehrende Debug: commands nachicht besser hervorheben (oder command ausgaben) vtl. mit "==="
- aktuelle locale vars anzeigen (ohne rest vom stack) ? (bzw alles über fp)
- auszug vom stack / daten ?
- wie mit Errors umgehen ? 
- vtl var angeben, die nach jedem step angezeigt wird