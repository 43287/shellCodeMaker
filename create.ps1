param (
    [string]$ProjectName
)

$scriptDir = Split-Path $MyInvocation.MyCommand.Path

$targetDir = Join-Path $scriptDir "x64\Release"

Set-Location -Path $targetDir

$exeName = "$ProjectName.exe"

if (Test-Path $exeName) {
    Write-Host "���� $exeName ..."
    & ".\$exeName"

} else {
    Write-Host "����δ�ҵ��ļ� $exeName"
    exit 1
}
