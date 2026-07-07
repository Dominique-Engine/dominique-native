# Research: Render Graphs

## Problem

Modern rendering has many passes and resources.

Manual pass ordering and resource lifetime management becomes fragile.

## Idea

Describe rendering as a dependency graph.

The engine schedules passes, creates transient resources, and inserts synchronization.

## Learning path

1. hardcoded pass sequence
2. simple graph with named resources
3. automatic pass ordering
4. transient resource allocation
5. barriers/synchronization
6. async compute scheduling
