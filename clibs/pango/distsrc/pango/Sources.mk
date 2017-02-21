libpango_1_0_la_SOURCES = break.c                                 \
                          ellipsize.c                             \
                          fonts.c                                 \
                          glyphstring.c                           \
                          modules.c                               \
                          pango-attributes.c                      \
                          pango-bidi-type.c                       \
                          pango-color.c                           \
                          pango-color-table.h                     \
                          pango-context.c                         \
                          pango-coverage.c                        \
                          pango-engine.c                          \
                          pango-engine-private.h                  \
                          pango-fontmap.c                         \
                          pango-fontset.c                         \
                          pango-glyph-item.c                      \
                          pango-gravity.c                         \
                          pango-impl-utils.h                      \
                          pango-item.c                            \
                          pango-language.c                        \
                          pango-language-sample-table.h           \
                          pango-layout.c                          \
                          pango-layout-private.h                  \
                          pango-markup.c                          \
                          pango-matrix.c                          \
                          pango-renderer.c                        \
                          pango-script.c                          \
                          pango-script-lang-table.h               \
                          pango-script-private.h                  \
                          pango-tabs.c                            \
                          pango-utils.c                           \
                          reorder-items.c                         \
                          shape.c                                 \
                          pango-enum-types.c                      \
                          module-defs-lang.c                      

pango_headers = pango.h                                 \
                pango-attributes.h                      \
                pango-bidi-type.h                       \
                pango-break.h                           \
                pango-context.h                         \
                pango-coverage.h                        \
                pango-engine.h                          \
                pango-font.h                            \
                pango-fontmap.h                         \
                pango-fontset.h                         \
                pango-glyph.h                           \
                pango-glyph-item.h                      \
                pango-gravity.h                         \
                pango-item.h                            \
                pango-language.h                        \
                pango-layout.h                          \
                pango-matrix.h                          \
                pango-modules.h                         \
                pango-renderer.h                        \
                pango-script.h                          \
                pango-tabs.h                            \
                pango-types.h                           \
                pango-utils.h                           

pangoft2_public_sources = pangofc-font.c                          \
                          pangofc-fontmap.c                       \
                          pangofc-decoder.c                       \
                          pangoft2.c                              

pangocairo_core_sources = pangocairo-context.c                    \
                          pangocairo-font.c                       \
                          pangocairo-fontmap.c                    \
                          pangocairo-render.c                     \
                          pangocairo-private.h                    

