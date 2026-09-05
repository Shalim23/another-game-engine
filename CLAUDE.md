# Project Rules

Rules and process only. Architecture, design, and technical decisions live in
separate docs (e.g. `docs/`) and are referenced from here, never duplicated here.

## Stack

Not decided yet. Once chosen, record it here (language, framework, build tooling).

## Coding rule: hints, not code

The user writes all game/engine code by hand, to keep the skill sharp. This
applies to everything — engine systems, editor, game logic, build config,
tooling, third-party glue. No default exemptions.

- Claude does NOT write or generate code by default, even boilerplate or config.
- Claude gives: step-by-step implementation plans, pseudocode, relevant
  API/function/module names, pointers to docs, and design tradeoffs.
- Exemptions are opt-in per instance only: if the user explicitly asks Claude
  to just write a specific piece, that's fine for that one instance. It is
  never a standing exemption for a category of files — ask again next time.

## Workflow

- **Design/planning**: for a new system or non-trivial change, use plan mode
  to work out the approach before any code is written.
- **Implementation**: hints/pseudocode only, per the rule above.
- **Review**: manual and on-demand. The user asks for a review (e.g.
  `/code-review`) when a chunk of work feels ready. No automatic gating on
  commits.

## Git process

- Every code change goes through a GitHub issue + PR. No direct commits/pushes
  to `main` — branch protection on `main` enforces this (PRs required, no
  force-push, no deletion, enforced for admins too).
- Issues are plain: descriptive title, description only if useful for later
  implementation. No labels, milestones, or other categorization for now.
- Every PR links its issue with a closing keyword (`Closes #N`) so merging
  auto-closes the issue — no separate manual step.
- Issue/project-state audits (are open issues still accurate, anything to
  close or rewrite) happen ad hoc, whenever asked — no fixed cadence.

## Roles

No standing architect/co-dev/tester personas. Instead:
- Plan mode covers architecture/design discussion.
- Implementation is hints-only pairing (see above).
- Review is a separate, fresh-context pass invoked on demand — independence
  comes from fresh context, not from a different persona.
