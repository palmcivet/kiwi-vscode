interface BaseNode {
  type: string;
  named: boolean;
}

interface ChildNode {
  multiple: boolean;
  required: boolean;
  types: BaseNode[];
}

type NodeInfo =
  | (BaseNode & {
    subtypes: BaseNode[];
  })
  | (BaseNode & {
    fields: { [name: string]: ChildNode };
    children: ChildNode[];
  });

interface Language {
  language: unknown;
  nodeTypeInfo: NodeInfo[];
}

declare const language: Language;
export = language;
