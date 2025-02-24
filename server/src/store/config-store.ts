class ConfigStore {
  private hasWorkspaceFolderCapability: boolean;
  private hasDiagnosticRelatedInformationCapability: boolean;
  private enableWarningDiagnostics: boolean;
  private enableFormatting: boolean;

  constructor() {
    this.hasWorkspaceFolderCapability = false;
    this.hasDiagnosticRelatedInformationCapability = false;
    this.enableWarningDiagnostics = true;
    this.enableFormatting = true;
  }

  public setWorkspaceFolderCapability(value: boolean): void {
    this.hasWorkspaceFolderCapability = value;
  }

  public hasWorkspaceFolders(): boolean {
    return this.hasWorkspaceFolderCapability;
  }

  public setDiagnosticRelatedInformationCapability(value: boolean): void {
    this.hasDiagnosticRelatedInformationCapability = value;
  }

  public hasDiagnosticRelatedInformation(): boolean {
    return this.hasDiagnosticRelatedInformationCapability;
  }

  public setEnableWarningDiagnostics(value: boolean): void {
    this.enableWarningDiagnostics = value;
  }

  public isWarningDiagnosticsEnabled(): boolean {
    return this.enableWarningDiagnostics;
  }

  public setEnableFormatting(value: boolean): void {
    this.enableFormatting = value;
  }

  public isFormattingEnabled(): boolean {
    return this.enableFormatting;
  }
}

export const configStore = new ConfigStore();
