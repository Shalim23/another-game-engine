---
description: Summarize open decisions, issues, PRs, and pending local changes
---

Give a concise project status report. Run these and summarize the results,
don't just dump raw output:

1. `gh issue list --state open` — split into two buckets by title: those
   starting with `Decide:` (open decisions/questions) and everything else
   (open feature/work issues).
2. `gh pr list --state open` — PRs awaiting review or merge.
3. `git status --short` — uncommitted local changes.
4. `git branch -vv` — local branches, noting any not tracking a remote or
   ahead/behind origin.

Structure the report as:
- **Open decisions** (from the `Decide:` issues)
- **Open work** (other open issues)
- **PRs awaiting merge**
- **Local working tree** (uncommitted changes, stray branches)
- **Suggested next step** (one line, only if something obviously needs
  attention — e.g. a stale branch, an old open decision, an easy next issue)

Keep it short. No filler, no restating the checklist.
