# Commit and PR Style

## Commit Message Rules

- PR title and body must follow the same style as regular commit messages.
- Do not use Conventional Commits (`feat:`, `fix:`, etc.).
- Start the subject line with an uppercase letter.
- Use imperative mood in the subject line, as in Git's own guidance (example: `Add ingreso shared labor fields`).
- Keep the first line concise and focused on what the commit does, with fewer than 75 characters.
- For larger or more complex changes, add a commit body:
- Leave one blank line after the first line.
- Then explain the changes using Markdown bullet points (`- item`) written in imperative mood.
- PR title and body should match this same regular commit-message style.
- Do not add a validation, tests, or checks section to PR bodies. Report validation in the assistant response unless the user explicitly asks for it in the PR body.
- Unless the user explicitly asks otherwise, open PRs as ready for review, not as drafts.
- Before creating a PR, re-read this section and state in the working update whether the PR must be ready for review or draft.
- When using a PR creation tool, explicitly set the draft option to `false` unless the user asked for a draft.
- After creating or modifying a PR, verify its state with repository tooling and confirm it is not a draft before reporting completion.
- If a PR is accidentally opened as draft and tooling cannot mark it ready for review, stop and ask the user before closing, recreating, or otherwise changing PR state.
- AI disclosure in the PR body for every AI-assisted change. Use an `Assisted-by` line in this format:
  - `Assisted-by: <tool/model>`