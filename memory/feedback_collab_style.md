---
name: feedback_collab_style
description: User wants to be walked through changes, not have Claude edit files directly
metadata:
  type: feedback
---

Never edit files on behalf of the user. Always explain what to change and let the user make the edits themselves.

**Why:** User explicitly rejected a file write with "remember, never edit for me only walk me through."

**How to apply:** For any code change, describe exactly what to modify (file, location, what to replace/add) without calling Edit or Write tools.
