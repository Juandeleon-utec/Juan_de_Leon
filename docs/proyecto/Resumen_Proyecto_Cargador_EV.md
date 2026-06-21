# Síntesis Académica del Proyecto

## Rediseño Estructural de Cargador Rápido para Vehículos Eléctricos

**Institución:** UTEC — Universidad Tecnológica del Uruguay
**Curso:** Posgrado en Fabricación Digital
**Autor:** Juan Pedro de León
**Estado del proyecto base:** Borrador 3 con imágenes
**Última actualización del sitio fuente:** 11-05-2026

> Esta página constituye la síntesis final del proceso documentado de forma narrativa en el sitio del proyecto. Mientras que el sitio relata la evolución cronológica de decisiones, errores y aprendizajes, este documento presenta de forma condensada y académica el objeto de estudio, las decisiones técnicas adoptadas y los resultados de validación obtenidos.

---

## 1. Resumen

El proyecto consistió en la reestructuración integral del diseño de un cargador rápido para vehículos eléctricos cuyo prototipo original presentaba limitaciones estructurales no subsanables mediante modificaciones parciales. Las causas identificadas incluyeron deficiencias en la distribución de carga del gabinete, ingreso de agua en componentes críticos, dificultades de transporte e instalación, y una dependencia significativa de proveedores externos sin control directo sobre el diseño. A esto se sumó un cambio de proveedor de fuentes de alimentación que obligó a redefinir la arquitectura interna del equipo.

En consecuencia, se descartó la línea de trabajo inicial —que contemplaba la integración de un biorreactor de algas como componente ambiental— y se reorientó el alcance del posgrado hacia un rediseño estructural completo, desarrollado desde cero en Autodesk Fusion 360, bajo los criterios de fabricabilidad, modularidad, robustez estructural y autonomía técnica.

---

## 2. Objeto de estudio y alcance

### 2.1 Objetivos del rediseño

El trabajo se planteó los siguientes objetivos específicos:

- Resolución de problemas de transporte e instalación en sitio.
- Mejora de la resistencia a la intemperie del gabinete.
- Reorganización completa de la estructura interna y corrección de la carga estructural.
- Diseño de bandejas específicas para los subsistemas eléctrico y electrónico.
- Mejora de los sistemas de ventilación y vedación.
- Reducción de la dependencia de terceros mediante capacidad de fabricación propia.
- Continuidad estética respecto al modelo anterior.
- Adaptación del producto a nuevas configuraciones de potencia y cambios de proveedores estratégicos.

### 2.2 Motivación

El análisis del prototipo existente evidenció que las problemáticas no podían resolverse mediante ajustes menores, identificándose como causas principales: fallas estructurales asociadas al peso y la carga del gabinete; ingreso de agua en componentes críticos; dificultades de transporte por dimensiones y distribución de masas; dependencia de proveedores externos sin control sobre el diseño; cambios en los proveedores de fuentes de alimentación que obligaron a reconsiderar el layout interno; y baja disponibilidad de materiales certificados en el interior de Uruguay.

A partir de este diagnóstico se optó por reiniciar el diseño completo, priorizando fabricabilidad, modularidad, robustez estructural, facilidad de ensamblaje y mantenimiento, capacidad de adaptación futura ante cambios de componentes, y mayor disponibilidad local de materiales y procesos productivos.

---

## 3. Desarrollo técnico

### 3.1 Cambio de proveedor del sistema de potencia

Se sustituyó el proveedor original de fuentes DC, Phoenix Contact (módulo CHARX PS-M2/825DC/1000DC, 30 kW, ~27 kg por unidad), por el proveedor Maxwell (módulo MXR100050B, 50 kW, ~23 kg por unidad). Esta migración respondió tanto a consideraciones de costo y disponibilidad comercial en Uruguay como al hecho de que el proyecto original había sido concebido asumiendo abastecimiento desde Brasil.

La nueva plataforma permite configuraciones de 50, 100 y 150 kW utilizando 3 fuentes en lugar de 4, lo que generó beneficios derivados en la relación costo/potencia instalada, una reducción del peso total del equipo, mayor espacio interno disponible, mejor circulación de aire y mayor facilidad de mantenimiento.

### 3.2 Sustitución del controlador principal y adecuación normativa

Se reemplazó el controlador previsto originalmente (Phoenix Contact EVPLC) por el **Vector vSECC.single**, en línea con estándares internacionales aplicables a infraestructura de carga rápida, incluyendo compatibilidad declarada con la norma IEC 61851.

Se incorporó adicionalmente un **IMD (Insulation Monitoring Device)** para la supervisión de fallas de aislamiento en el bus DC de hasta 1000 VDC, y una **contactora principal DC de 400 A** que permite desenergizar exclusivamente las fuentes de potencia ante una condición de falla, manteniendo operativo el controlador y preservando capacidad de diagnóstico y registro de eventos.

### 3.3 Monitoreo remoto y conectividad GSM

Se incorporó un circuito de telemetría con conectividad GSM/datos móviles, orientado a habilitar a futuro un dashboard centralizado de supervisión. Las variables previstas incluyen estado general del equipo, detección de alarmas, energía entregada por sesión, tiempo de carga y estado de comunicación con periféricos.

### 3.4 Integración con Raspberry Pi

Mediante bus I2C se integró una Raspberry Pi con el software PiSignage y un servidor Apache/PHP local, destinada a funciones de interfaz visual: visualización del estado de carga, indicadores operativos y reproducción de contenido institucional o publicitario en la pantalla del equipo.

---

## 4. Caracterización de materiales y diseño estructural

El despiece estructural —compuesto por perfiles L, U, C y tubo cuadrado en acero comercial— totaliza aproximadamente 26.5 m de perfilería y un peso estructural estimado de **44.3 kg**, valor considerado adecuado para equilibrar rigidez, facilidad de transporte y carga sobre los puntos de anclaje.

Para la validación estructural mediante simulación por elementos finitos (sección 5) se utilizó como material de la estructura **Acero AISI 1015**, con las siguientes propiedades:

| Propiedad | Valor |
|---|---|
| Densidad | 7.87 g/cm³ |
| Módulo de Young (E) | 205 GPa |
| Coeficiente de Poisson | 0.29 |
| Límite de elasticidad (Fy) | 285 MPa |
| Resistencia máxima a tracción (Fu) | 385 MPa |

Estos valores son consistentes con la categoría de acero al carbono estructural adoptada como referencia preliminar en etapas tempranas del proyecto (equivalente a ASTM A36/A500/S235), con la diferencia de que corresponden a la caracterización específica del material efectivamente utilizado en el modelo validado, en lugar de un rango genérico de referencia.

---

## 5. Validación estructural mediante análisis por elementos finitos (FEA)

Como parte de la validación del soporte de izado de la estructura, se realizó un estudio de tensión estática en Autodesk Fusion 360 sobre el caso de carga máxima de la familia de productos (configuración con tres fuentes de alimentación), que por dominancia estructural cubre la totalidad de las variantes comerciales del equipo (configuraciones de una, dos y tres fuentes).

### 5.1 Metodología

- Peso real total del cargador: 112 kg.
- Factor de izaje aplicado sobre la carga real: 1.5, conforme a criterios habituales de diseño de dispositivos de izaje.
- Aplicación de carga diferenciada por origen: peso propio de la estructura modelada mediante gravedad factorizada (14.71 m/s²), y peso de componentes no modelados como sólidos (fuentes, cableado, gabinete) mediante cuatro fuerzas puntuales de 350 N aplicadas en los parantes verticales de transmisión de carga.
- Restricciones: dos puntos fijos, representando los anclajes reales de izaje de la estructura.
- Material: Acero AISI 1015 (límite de fluencia 285 MPa).

### 5.2 Resultados

| Parámetro | Valor obtenido |
|---|---|
| Factor de Seguridad mínimo | 2.253 |
| Rango objetivo de diseño | 2.0 – 4.0 |
| Tensión de von Mises máxima | 126.5 MPa |
| Desplazamiento máximo | 0.96 mm |
| Reacción en punto de anclaje 1 | 832.0 N |
| Reacción en punto de anclaje 2 | 832.4 N |

### 5.3 Conclusión del estudio

El Factor de Seguridad mínimo obtenido (2.25) se ubica dentro del rango objetivo definido (2.0–4.0), con un margen del 12.6% respecto al límite inferior aceptable. La distribución de reacciones entre ambos puntos de anclaje resulta prácticamente simétrica, validando la geometría de izaje propuesta. Bajo los criterios de análisis empleados, no se espera deformación permanente ni falla del componente estructural ante la carga de diseño establecida.

*Los informes completos de simulación (Autodesk Fusion 360) se anexan como documentación complementaria — ver sección de Referencias.*

---

## 6. Dificultades identificadas

- El diseño original resultó estructuralmente no recuperable mediante ajustes parciales.
- Los sucesivos cambios de proveedor obligaron a replantear decisiones internas durante el desarrollo, en un contexto donde el proyecto había sido originalmente concebido para abastecimiento desde Brasil, mercado con condiciones de disponibilidad distintas a las de Uruguay.
- La reconstrucción del listado completo de partes demandó más tiempo del previsto inicialmente.
- Fue necesaria la adquisición de nuevas competencias técnicas, en particular soldadura MIG, para sostener la estrategia de fabricación propia.
- Se requirió equilibrar la continuidad estética del producto con una reestructuración interna profunda.

---

## 7. Resultados y estado actual

Como resultado del proceso se obtuvo un nuevo modelo estructural completo, desarrollado íntegramente en Fusion 360, con un diseño más robusto, modular y mantenible, y con mejor comportamiento frente a transporte e instalación, validado mediante el análisis estructural de izaje descrito en la sección 5. Se logró además mayor autonomía técnica, al contar con control total sobre el modelo CAD para futuros ajustes derivados de cambios de proveedor, y se incorporó capacidad de fabricación propia mediante la adquisición de competencias y equipamiento de soldadura MIG.

Al cierre de este documento, se encuentran en ejecución las perforaciones del gabinete (ventilación, salida de cables de carga, iluminación externa y soporte del conector CCS2 con iluminación LED WS2812B programable). La fabricación del primer prototipo, originalmente prevista para febrero de 2026, fue reprogramada para mayo de 2026 debido a las dificultades documentadas.

---

## 8. Próximos pasos

- Validación del diseño mediante fabricación real.
- Ajuste de detalles en función de pruebas físicas.
- Documentación de nuevas iteraciones del proyecto.
- Integración de los aprendizajes derivados del proceso de soldadura al flujo de diseño en Fusion 360.

---

## 9. Referencias y documentación anexa

### 9.1 Documento fuente

1. de León, J. P. (2026). *Documentación del Proyecto — Rediseño estructural de cargador rápido para vehículos eléctricos*. Posgrado en Fabricación Digital, UTEC. Borrador 3 con imágenes, actualización 11-05-2026.

### 9.2 Informes de simulación estructural (anexos)

2. de León, J. P. (2026). *Informe de simulación FEA — Estudio 1: Tensión estática (versión preliminar, v40)*. Autodesk Fusion 360 (2703.1.20). Archivo: MOVEV_Final_May_V_1_3_Nayax_Notebook_1 v40. Creado 2026-06-21.
3. de León, J. P. (2026). *Informe de simulación FEA — Estudio 1: Tensión estática (versión corregida y validada, v41)*. Autodesk Fusion 360 (2703.1.20). Archivo: MOVEV_Final_May_V_1_3_Nayax_Notebook_1 v41. Creado 2026-06-21.

### 9.3 Repositorio de archivos del proyecto

4. *Cargador_EV_Estructura_v3.f3d* — Autodesk Fusion 360 (editable). Archivo maestro del proyecto, con historial paramétrico, componentes y estructura general del cargador.
5. *Excel con resumen de piezas y compras* — Formato XLSX. Listado de materiales, cantidades y clasificación por categorías para compra en plaza de hierros y proveedores locales.
6. *Proyectos eléctricos y PCB* — KiCad (imágenes). Esquemáticos eléctricos, diseño de placas PCB y documentación técnica asociada al sistema electrónico del cargador.
7. *Tablero de desarrollo del proyecto* — Miro Board (en línea). Espacio de trabajo visual con referencias, ideas, evolución del diseño y documentación complementaria.

### 9.4 Referencias técnicas externas citadas

8. Phoenix Contact. *Módulo de potencia DC CHARX PS-M2/825DC/1000DC/30kW*. Disponible en: https://www.phoenixcontact.com/pt-br/produtos/modulo-de-potencia-dc-charx-ps-m2-825dc-1000dc-30kw-1296467
9. Maxwell Power. *MXR100050B*. Disponible en: https://www.maxwellpower.cn/productinfo/2413106.html
10. UNIT — Instituto Uruguayo de Normas Técnicas. *Norma IEC 61851*. Disponible en: https://www.unit.org.uy/normalizacion/norma/100001554

### 9.5 Herramientas de apoyo declaradas

11. Google Gemini — utilizada para refinamiento de texto, corrección de estilo y gramática de la documentación del sitio del proyecto (declarado bajo esquema de Contribución Cognitiva, CCL).
